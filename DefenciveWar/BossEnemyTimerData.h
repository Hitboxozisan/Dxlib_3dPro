#pragma once

#include <unordered_map>
#include "BossEnemyTimerType.h"

namespace BossTimer
{

	std::unordered_map<TimerType, float> TIMER =
	{
		{TimerType::VibrateAttack, VIBRATE_TIME},
		{TimerType::ShotInterval, SHOT_INTERVAL},
		{TimerType::Landing, LANDING_TIME},
		{TimerType::Tracking, TRACKING_TIME},
	};
}
