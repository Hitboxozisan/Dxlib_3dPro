#pragma once

const float TRANK_COOLTIME = 10.0f;
const float VIBRATE_TIME = 2.0f;
const float FINISH_VIBRATE_TIME = 4.0f;
const float SHOT_INTERVAL = 1.0f;
const float LANDING_TIME = 2.0f;
const float TELEPORT_TIME = 1.5f;

enum class TimerType
{
	TrunkCool,
	VibrateAttack,
	VibrateFinish,
	ShotInterval,
	Landing,
	Teleport,

	TimerAmount,
};