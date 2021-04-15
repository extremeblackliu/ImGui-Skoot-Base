#include <thread>
#include "Hooks.h"
#include "Utils\Utils.h"
#include "Features\Features.h"
#include "menu/Menu.h"
#include "menu/MenuFonts.h"
#include "menu/MenuBackground.h"

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

Misc     g_Misc;
Hooks    g_Hooks;

void Hooks::Init()
{
    // Get window handle
    while (!(g_Hooks.hCSGOWindow = FindWindowA("Valve001", nullptr)))
    {
        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(50ms);
    }

    interfaces::Init();                         // Get interfaces
    g_pNetvars = std::make_unique<NetvarTree>();// Get netvars after getting interfaces as we use them

    Utils::Log("Hooking in progress...");

    // D3D Device pointer
    const uintptr_t d3dDevice = **reinterpret_cast<uintptr_t**>(Utils::FindSignature("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);

    if (g_Hooks.hCSGOWindow)        // Hook WNDProc to capture mouse / keyboard input
        g_Hooks.pOriginalWNDProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(g_Hooks.hCSGOWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Hooks::WndProc)));

    // VMTHooks
    g_Hooks.pD3DDevice9Hook = std::make_unique<VMTHook>(reinterpret_cast<void*>(d3dDevice));
    g_Hooks.pClientModeHook = std::make_unique<VMTHook>(g_pClientMode);
    g_Hooks.pSurfaceHook    = std::make_unique<VMTHook>(g_pSurface);

    // Hook the table functions
    g_Hooks.pD3DDevice9Hook->Hook(vtable_indexes::reset,      Hooks::Reset);
    g_Hooks.pD3DDevice9Hook->Hook(vtable_indexes::endscene,   Hooks::EndScene);
    g_Hooks.pClientModeHook->Hook(vtable_indexes::createMove, Hooks::CreateMove);
    g_Hooks.pSurfaceHook   ->Hook(vtable_indexes::lockCursor, Hooks::LockCursor);

    Utils::Log("Hooking completed!");
}

void Hooks::Restore()
{
	Utils::Log("Unhooking in progress...");
    {   // Unhook every function we hooked and restore original one
        g_Hooks.pD3DDevice9Hook->Unhook(vtable_indexes::endscene);
        g_Hooks.pD3DDevice9Hook->Unhook(vtable_indexes::reset);
        g_Hooks.pClientModeHook->Unhook(vtable_indexes::createMove);
        g_Hooks.pSurfaceHook   ->Unhook(vtable_indexes::lockCursor);
        SetWindowLongPtr(g_Hooks.hCSGOWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(g_Hooks.pOriginalWNDProc));

        g_pNetvars.reset();   /* Need to reset by-hand, global pointer so doesnt go out-of-scope */
    }
    Utils::Log("Unhooking succeded!");
}

bool __fastcall Hooks::CreateMove(IClientMode* thisptr, void* edx, float sample_frametime, CUserCmd* pCmd)
{
    // Call original createmove before we start screwing with it
    static auto oCreateMove = g_Hooks.pClientModeHook->GetOriginal<CreateMove_t>(24);
    oCreateMove(thisptr, edx, sample_frametime, pCmd);

    if (!pCmd || !pCmd->command_number)
        return oCreateMove;

    // Get globals
    g::pCmd         = pCmd;
    g::pLocalEntity = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());
    if (!g::pLocalEntity)
        return oCreateMove;

    g_Misc.OnCreateMove();
    // run shit outside enginepred

    engine_prediction::RunEnginePred();
    // run shit in enginepred
    engine_prediction::EndEnginePred();

    return false;
}

void __fastcall Hooks::LockCursor(ISurface* thisptr, void* edx)
{
    static auto oLockCursor = g_Hooks.pSurfaceHook->GetOriginal<LockCursor_t>(vtable_indexes::lockCursor);

    if (!g_Menu.bMenuOpened)
        return oLockCursor(thisptr, edx);

    g_pSurface->UnlockCursor();
}

long __stdcall Hooks::EndScene(IDirect3DDevice9* pDevice)
{
    static auto oEndScene = g_Hooks.pD3DDevice9Hook->GetOriginal<EndScene_t>(vtable_indexes::endscene);

    DWORD colorwrite, srgbwrite;
    IDirect3DVertexDeclaration9* vert_dec = nullptr;
    IDirect3DVertexShader9* vert_shader = nullptr;
    DWORD dwOld_D3DRS_COLORWRITEENABLE = NULL;
    pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
    pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &srgbwrite);

    pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
    pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

    pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
    pDevice->GetVertexDeclaration(&vert_dec);
    pDevice->GetVertexShader(&vert_shader);
    pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
    pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
    pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
    pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
    pDevice->SetSamplerState(NULL, D3DSAMP_SRGBTEXTURE, NULL);

    if (!g_Hooks.bInitializedDrawManager)
    {
        IDirect3DSwapChain9* chain = nullptr;
        D3DPRESENT_PARAMETERS pp;
        D3DDEVICE_CREATION_PARAMETERS cp;

        pDevice->GetCreationParameters(&cp);
        pDevice->GetSwapChain(0, &chain);

        if (chain)
            chain->GetPresentParameters(&pp);

        ImGui::CreateContext();
        ImGui_ImplWin32_Init(cp.hFocusWindow);
        ImGui_ImplDX9_Init(pDevice);

        ImGuiIO& io = ImGui::GetIO();

        g::menuFont = io.Fonts->AddFontFromMemoryCompressedTTF(verdana_compressed_data, verdana_compressed_size, 12, NULL, io.Fonts->GetGlyphRangesCyrillic());
        g::tabFont = io.Fonts->AddFontFromMemoryCompressedTTF(cherryfont_compressed_data, cherryfont_compressed_size, 40, NULL, io.Fonts->GetGlyphRangesCyrillic());
        g::controlFont = io.Fonts->AddFontFromMemoryCompressedTTF(comboarrow_compressed_data, comboarrow_compressed_size, 12, NULL, io.Fonts->GetGlyphRangesCyrillic());
        g::boldMenuFont = io.Fonts->AddFontFromMemoryCompressedTTF(verdanab_compressed_data, verdanab_compressed_size, 11, NULL, io.Fonts->GetGlyphRangesCyrillic());

        if (g::menuBg == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(pDevice, &menuBackground, sizeof(menuBackground), 1000, 1000, D3DUSAGE_DYNAMIC, 0, D3DFMT_X8B8G8R8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &g::menuBg);

        g_Hooks.bInitializedDrawManager = true;
    }

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (g_Menu.bMenuOpened)
        g_Menu.Render();

    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, colorwrite);
    pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, srgbwrite);
    pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);
    pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
    pDevice->SetVertexDeclaration(vert_dec);
    pDevice->SetVertexShader(vert_shader);

    return oEndScene(pDevice);
}

HRESULT __stdcall Hooks::Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    static auto oReset = g_Hooks.pD3DDevice9Hook->GetOriginal<Reset_t>(vtable_indexes::reset);

    ImGui_ImplDX9_InvalidateDeviceObjects();
    ImGui_ImplDX9_CreateDeviceObjects();

    return oReset(pDevice, pPresentationParameters);
}

LRESULT Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // for now as a lambda, to be transfered somewhere
    // Thanks uc/WasserEsser for pointing out my mistake!
    // Working when you HOLD th button, not when you press it.
    const auto getButtonHeld = [uMsg, wParam](bool& bButton, int vKey)
    {
        if (wParam != vKey) return;

        if (uMsg == WM_KEYDOWN)
            bButton = true;
        else if (uMsg == WM_KEYUP)
            bButton = false;
    };

    const auto getButtonToggle = [uMsg, wParam](bool& bButton, int vKey)
    {
        if (wParam != vKey) return;

        if (uMsg == WM_KEYUP)
            bButton = !bButton;
    };

    getButtonToggle(g_Menu.bMenuOpened, VK_INSERT);
    g_InputSystem->EnableInput(!g_Menu.bMenuOpened);

    ImGui::CreateContext();

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) && g_Menu.bMenuOpened)
        return true;

    // Call original wndproc to make game use input again
    return CallWindowProcA(g_Hooks.pOriginalWNDProc, hWnd, uMsg, wParam, lParam);
}
