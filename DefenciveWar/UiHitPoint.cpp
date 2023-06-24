#include "common.h"
#include "UiHitPoint.h"
#include "Singleton.h"
#include "DeltaTime.h"
#include "Timer.h"
#include "ImageManager.h"
#include "SceneGame.h"
#include "Player.h"
#include "Random.h"

UiHitPoint::UiHitPoint(class SceneGame* objData)
	:deltaTime(Singleton<DeltaTime>::GetInstance())
	,random(Singleton<Random>::GetInstance())
{
	data = objData;
	vibrateTimer = new Timer(VIBRATE_TIME);
	deferredHpTimer = new Timer(DEFERRED_TIME);

	// UI画像読み込み
	param.handle = imageMgr.GetImage(ImageType::PlayerHpGauge);
}

UiHitPoint::~UiHitPoint()
{
	delete vibrateTimer;
	delete deferredHpTimer;
}

void UiHitPoint::Initialize()
{
	int hp = data->GetPlayer()->GetHitpoint();
	int maxHp = data->GetPlayer()->GetMaxHitpoint();

	// Ui画像座標
	param.pos = INITIAL_POS;
	param.prevPos = param.pos;

	// Hpゲージ座標
	gauge.posL.x = 55, gauge.posL.y = 980;
	gauge.posR.x = gauge.posL.x + 490 * ( hp / maxHp ), gauge.posR.y = 1015;
	gauge.prevPosL = gauge.posL;
	gauge.prevPosR = gauge.posR;

	// ダメージ用Hpゲージ座標
	damageGauge.posL = gauge.posL;
	damageGauge.posR = gauge.posR;
	damageGauge.prevPosL = gauge.prevPosL;
	damageGauge.prevPosR = gauge.prevPosR;

	// 粒子エフェクト初期化
	for (int i = 0; i < 100; i++)
	{
		hpPixel[i].pos = ZERO_VECTOR;
		//hpPixel[i].createPos = ZERO_VECTOR;
		hpPixel[i].exist = false;
	}
}

void UiHitPoint::Update()
{
	//UpdateValue();
	//VibrateUi();
	CreateHpGaugePixel();
	MoveGaugePixel();
}

void UiHitPoint::Draw()
{
	int hp = data->GetPlayer()->GetHitpoint();
	int maxHp = data->GetPlayer()->GetMaxHitpoint();

	gauge.posR.x = gauge.posL.x + 490 * (hp / maxHp);
	damageGauge.posR.x = damageGauge.posL.x + 490 * (damageGauge.hp / maxHp);

	// ダメージ時の遅延減少用のHitPoint
	DrawBox(damageGauge.posL.x, damageGauge.posL.y, damageGauge.posR.x, damageGauge.posR.y, RED, TRUE);
	// プレイヤーのHitPointを表示
	DrawBox(gauge.posL.x, gauge.posL.y, gauge.posR.x, gauge.posR.y, GREEN, TRUE);
	// ゲージピクセル描画
	for (int i = 0; i < 100; ++i)
	{
		// 存在しないなら描画しない
		if (hpPixel[i].exist)
		{
			DrawCircle(hpPixel[i].pos.x, hpPixel[i].pos.y, PIXEL_RADIUS, WHITE, TRUE);
		}
	}
	// HitPointゲージ枠表示
	DrawRotaGraph(param.pos.x, param.pos.y, 0.8f, 0.0f, param.handle, TRUE);
}

void UiHitPoint::UpdateValue()
{
}

void UiHitPoint::VibrateUi()
{
}

void UiHitPoint::DecreaseHitPoint()
{


}

void UiHitPoint::CreateHpGaugePixel()
{
	int randomY;
	int randomSpeed;

	for (int i = 0; i < 100; i++)
	{
		// 存在しない場合生成する
		if (!hpPixel[i].exist)
		{
			// 発生位置設定
			randomY = random.GetRandomInt(gauge.posL.y, gauge.posR.y);
			// 移動速度設定
			randomSpeed = random.GetRandomInt(PIXEL_MOVE_SPEED_MIN, PIXEL_MOVE_SPEED_MAX);

			hpPixel[i].pos.x = gauge.posL.x;
			hpPixel[i].pos.y = randomY;
			//hpPixel[i].createPos.y = randomY;
			hpPixel[i].speed = randomSpeed;
			hpPixel[i].exist = true;
		}
	}
}

void UiHitPoint::MoveGaugePixel()
{
	float delta = deltaTime.GetDeltaTime();

	for (int i = 0; i < 100; i++)
	{
		hpPixel[i].pos.x += hpPixel[i].speed * delta;
	
		if (hpPixel[i].pos.x >= gauge.posR.x)
		{
			hpPixel[i].exist = false;
		}
	}
}
