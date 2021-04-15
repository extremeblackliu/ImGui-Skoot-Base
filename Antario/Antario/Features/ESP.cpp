#include "ESP.h"
#include "..\Utils\Utils.h"
#include "..\SDK\IVEngineClient.h"
#include "..\SDK\PlayerInfo.h"

ESP g_ESP;

void ESP::RenderBox(C_BaseEntity* pEnt)
{
}

void ESP::RenderName(C_BaseEntity* pEnt, int iterator)
{
}

void ESP::RenderWeaponName(C_BaseEntity* pEnt)
{
}


void ESP::Render()
{
    if (!g::pLocalEntity || !g_pEngine->IsInGame())
        return;

    for (int it = 1; it <= g_pEngine->GetMaxClients(); ++it)
    {
        C_BaseEntity* pPlayerEntity = g_pEntityList->GetClientEntity(it);
        
        if (!pPlayerEntity
            || pPlayerEntity == g::pLocalEntity
            || pPlayerEntity->IsDormant()
            || !pPlayerEntity->IsAlive())
            continue;
    }
}
