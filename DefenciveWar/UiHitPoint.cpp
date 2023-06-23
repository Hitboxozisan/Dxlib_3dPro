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

	// UI�摜�ǂݍ���
	param.handle = imageMgr.GetImage(ImageType::PlayerHitpoint);
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

	// Ui�摜���W
	param.pos = INITIAL_POS;
	param.prevPos = param.pos;

	// Hp�Q�[�W���W
	gauge.posL.x = 55, gauge.posL.y = 980;
	gauge.posR.x = gauge.posL.x + 490 * ( hp / maxHp ), gauge.posR.y = 1015;
	gauge.prevPosL = gauge.posL;
	gauge.prevPosR = gauge.posR;

	// �_���[�W�pHp�Q�[�W���W
	damageGauge.posL = gauge.posL;
	damageGauge.posR = gauge.posR;
	damageGauge.prevPosL = gauge.prevPosL;
	damageGauge.prevPosR = gauge.prevPosR;

	// ���q�G�t�F�N�g������
	for (int i = 0; i < sizeof(hpPixel); i++)
	{
		hpPixel[i].pos = ZERO_VECTOR;
		hpPixel[i].createPos = ZERO_VECTOR;
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

	// �_���[�W���̒x�������p��HitPoint
	DrawBox(damageGauge.posL.x, damageGauge.posL.y, damageGauge.posR.x, damageGauge.posR.y, RED, TRUE);
	// �v���C���[��HitPoint��\��
	DrawBox(gauge.posL.x, gauge.posL.y, gauge.posR.x, gauge.posR.y, GREEN, TRUE);
	// �Q�[�W�s�N�Z���`��
	for (int i = 0; i < sizeof(hpPixel); ++i)
	{
		// ���݂��Ȃ��Ȃ�`�悵�Ȃ�
		if (hpPixel[i].exist)
		{
			DrawCircle(hpPixel[i].pos.x, hpPixel[i].pos.y, PIXEL_RADIUS, WHITE, TRUE);
		}
	}
	// HitPoint�Q�[�W�g�\��
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

	for (int i = 0; i < sizeof(hpPixel); i++)
	{
		// �����ʒu�ݒ�
		randomY = random.GetRandomInt(980, 1015);
		// �ړ����x�ݒ�
		randomSpeed = random.GetRandomInt(PIXEL_MOVE_SPEED_MIN, PIXEL_MOVE_SPEED_MAX);

		hpPixel[i].pos.x = gauge.posL.x + PIXEL_RADIUS;
		hpPixel[i].pos.y = randomY;
		hpPixel[i].createPos.y = randomY;
		hpPixel[i].speed = randomSpeed;
		hpPixel[i].exist = true;
	}
}

void UiHitPoint::MoveGaugePixel()
{
	for (int i = 0; i < sizeof(hpPixel); i++)
	{
		hpPixel[i].pos.x += hpPixel[i].speed;
	
		if (hpPixel[i].pos.x >= gauge.posR.x)
		{
			hpPixel[i].exist = false;
		}
	}
}
