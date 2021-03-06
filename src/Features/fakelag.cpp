#include "fakelag.h"

#include "../settings.h"
#include "../interfaces.h"
#include "../Hooks/hooks.h"
#include <climits>

#ifndef absol
        #define absol(x) x < 0 ? -x : x
#endif

int ticksMax = 50;
int ticks_allowed = 0;
void FakeLag::CreateMove(CUserCmd* cmd)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;
	if (!Settings::FakeLag::enabled)
		return;
	if (engine->IsVoiceRecording())
                return;
		int velocity2d = localplayer->GetVelocity().Length2D();
                int max_choke;
 const auto netchannel = GetLocalClient(-1)->m_NetChannel;
  int pakets = netchannel->m_nChokedPackets;

		  FakeLag::shift = 0;
       	FakeLag::should_recharge = false;

        if (FakeLag::should_recharge)
        {
                ++ticks_allowed;
                CreateMove::sendPacket = true;

                cmd->tick_count = INT_MAX;
                cmd->forwardmove = 0.0f;
                cmd->sidemove = 0.0f;
                cmd->upmove = 0.0f;
                cmd->buttons &= ~IN_ATTACK;
                cmd->buttons &= ~IN_ATTACK2;

                if (ticks_allowed >= 14)
                {
	//		cvar->ConsoleDPrintf(XORSTR("we charged bois"));
                  //      FakeLag::should_recharge = false;
                       // *(bool*)(*frame_ptr - 0x1C) = true; 
                }

        }
		//if (ticks_allowed < 14)
		//FakeLag::should_recharge = true;
		//if (FakeLag::should_recharge)
		//	return;
	        if (cmd->buttons & IN_ATTACK)
	        {
                CreateMove::sendPacket = true;
   		C_BaseCombatWeapon* activeWeapon = ( C_BaseCombatWeapon* ) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon() );

		if (Settings::FakeLag::ChokeOnShot && activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_GRENADE)
		max_choke = 25;
    		}

		if (Settings::FakeLag::adaptive){
		if (velocity2d >= 5.0f)
                {
                        auto dynamic_factor = std::ceil(64.0f / (velocity2d * globalVars->interval_per_tick));

                        if (dynamic_factor > 16)
                                dynamic_factor = Settings::FakeLag::value;

                        max_choke = dynamic_factor;
                }
                else
                        max_choke = Settings::FakeLag::value;
		}else if ( !(cmd->buttons & IN_ATTACK) || !(Settings::FakeLag::ChokeOnShot) ) max_choke = Settings::FakeLag::value;

		 if (FakeLag::ticks >= max_choke || ((*csGameRules)->IsValveDS() && pakets > 6)){
			CreateMove::sendPacket = true;
			FakeLag::ticks = -1;
		}else{
			CreateMove::sendPacket = false;
		}
	FakeLag::ticks++;
}

