#pragma once
#include "..\Utils\GlobalVars.h"


class ESP
{
public:
    void Render();
private:
    void RenderBox(C_BaseEntity* pEnt);
    void RenderName(C_BaseEntity* pEnt, int iterator);
    void RenderWeaponName(C_BaseEntity* pEnt);
};
extern ESP g_ESP;