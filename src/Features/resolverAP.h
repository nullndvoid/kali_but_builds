#pragma once


#include <vector>
#include <cstdint>
#include "../SDK/definitions.h"
#include "../SDK/IGameEvent.h"
#include "../Utils/entity.h"
#include "../Utils/math.h"
#include "../Utils/xorstring.h"
#include "../interfaces.h"
#include "../settings.h"

namespace ResolverAP
{
extern std::vector<int64_t> Players;

	//Hooks

	void FrameStageNotify(ClientFrameStage_t stage);
	void PostFrameStageNotify(ClientFrameStage_t stage);
	void FireGameEvent(IGameEvent* event);
}
