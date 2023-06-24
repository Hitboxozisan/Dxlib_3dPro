#pragma once

#include "UiBase.h"

class UiHitPoint final : public UiBase
{
public:
	UiHitPoint(class SceneGame* objData);
	~UiHitPoint();

	void Initialize();
	void Update();
	void Draw();

private:
	const VECTOR INITIAL_POS = VGet(300, 1000, 0);
	const int	PIXEL_MOVE_SPEED_MAX = 100;		// HitPointゲージ最大移動速度
	const int	PIXEL_MOVE_SPEED_MIN = 50;		// HitPointゲージ最小移動速度
	const int	PIXEL_RADIUS = 1;
	const float DECREASE_HITPOINT = 50.0f;		// HitPoint減少量
	const float VIBRATE_TIME = 0.3f;			// 振動時間
	const float DEFERRED_TIME = 0.5f;			// 減少するまでの時間

	void UpdateValue();						// 各種値を更新する
	void VibrateUi();						// Uiを振動させる
	void DecreaseHitPoint();				// HitPointを減少させる
	void CreateHpGaugePixel();				// HitPointゲージエフェクトを生成
	void MoveGaugePixel();					// 粒子の移動処理

	// ゲージ上の粒子エフェクト
	struct HitpointEffect
	{
		VECTOR pos;				// 粒子位置
		int speed;				// 移動速度
		bool exist;				// 存在しているか
	};
	
	struct HitpointGauge
	{
		// ゲージ右下頂点
		VECTOR posR;
		VECTOR prevPosR;
		// ゲージ左上頂点
		VECTOR posL;
		VECTOR prevPosL;
	};
	
	struct SecondHitPointGauge
	{
		// 遅れて減少する用のHitpoint
		int hp;
		// ゲージ右下頂点
		VECTOR posR;
		VECTOR prevPosR;
		// ゲージ左上頂点
		VECTOR posL;
		VECTOR prevPosL;
	};

	class DeltaTime& deltaTime;
	class Random& random;
	class Timer* vibrateTimer;
		  Timer* deferredHpTimer;

	HitpointEffect hpPixel[100];
	HitpointGauge gauge;
	SecondHitPointGauge damageGauge;
};

