#pragma once

namespace BossState
{
	// ボスの行動状態
	enum class State
	{
		Assault,		// 対象に突進する
		BulletNormal,	// 弾を発射する（1発ずつ）
		Stomp,			// 対象を踏みつける
		Slide,			// 跳ね返された

		StateAmound,
	};
}
