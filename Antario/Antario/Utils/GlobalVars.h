#pragma once

#include "..\SDK\CInput.h"
#include <d3d9.h>
#include "..\SDK\CEntity.h"
#include "..\imgui\imgui.h"

namespace g
{
    extern CUserCmd*      pCmd;
    extern C_BaseEntity*  pLocalEntity;
    extern std::uintptr_t uRandomSeed;
    extern ImFont* menuFont;
    extern ImFont* tabFont;
    extern ImFont* controlFont;
    extern ImFont* boldMenuFont;
    extern IDirect3DTexture9* menuBg;
}
