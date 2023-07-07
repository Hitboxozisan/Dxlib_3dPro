#pragma once

const float TRANK_COOLTIME = 10.0f;
const float VIBRATE_TIME = 2.0f;
const float FINISH_VIBRATE_TIME = 4.0f;
const float SHOT_INTERVAL = 1.0f;
const float LANDING_TIME = 2.0f;
const float TRACKING_TIME = 3.0f;
const float TELEPORT_TIME = 1.5f;

enum class TimerType
{
	TrunkCool,
	VibrateAttack,		// 振動時間（突進攻撃）
	VibrateFinish,		// 振動時間（ゲーム終了時）
	ShotInterval,		// 発射間隔
	Landing,			// 踏みつけを行うまでの待機時間
	Tracking,			// 踏みつけ位置決定までの追跡時間
	Teleport,

	TimerAmount,
};