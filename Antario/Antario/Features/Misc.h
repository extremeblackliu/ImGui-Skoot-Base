#pragma once

#include "..\Utils\GlobalVars.h"

class Misc
{
public:
    void OnCreateMove()
    {
        this->pCmd   = g::pCmd;
        this->pLocal = g::pLocalEntity;

        this->DoBhop();
        // sum future shit
    };
private:
    CUserCmd*     pCmd;
    C_BaseEntity* pLocal;

    void DoBhop() const
    {
        if (this->pLocal->GetMoveType() == MoveType_t::MOVETYPE_LADDER)
            return;

        static bool bLastJumped = false;
        static bool bShouldFake = false;

        if (!bLastJumped && bShouldFake)
        {
            bShouldFake = false;
            pCmd->buttons |= IN_JUMP;
        }
        else if (pCmd->buttons & IN_JUMP)
        {
            if (pLocal->GetFlags() & FL_ONGROUND)
                bShouldFake = bLastJumped = true;
            else 
            {
                pCmd->buttons &= ~IN_JUMP;
                bLastJumped = false;
            }
        }
        else
            bShouldFake = bLastJumped = false;
    }
};

extern Misc g_Misc;
