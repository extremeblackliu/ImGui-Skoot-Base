#include "GlobalVars.h"

namespace g
{
    CUserCmd*      pCmd         = nullptr;
    C_BaseEntity*  pLocalEntity = nullptr;
    std::uintptr_t uRandomSeed  = NULL;
    ImFont* menuFont;
    ImFont* tabFont;
    ImFont* controlFont;
    ImFont* boldMenuFont;
    IDirect3DTexture9* menuBg;
}
