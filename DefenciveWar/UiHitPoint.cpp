#include "common.h"
#include "UiHitPoint.h"
#include "Singleton.h"
#include "DeltaTime.h"
#include "Timer.h"
#include "ImageManager.h"
#include "SceneGame.h"
#include "Player.h"
#include "Random.h"

using namespace Math3d;

UiHitPoint::UiHitPoint(class SceneGame* objData)
	:deltaTime(Singleton<DeltaTime>::GetInstance())
	,random(Singleton<Random>::GetInstance())
{
	data = objData;
	vibrateTimer = new Timer(VIBRATE_TIME);
	deferredHpTimer = new Timer(DEFERRED_TIME);

	// UI�摜�ǂݍ���
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

	// Ui�摜���W
	param.pos = INITIAL_POS;
	param.prevPos = param.pos;

	// Hp�Q�[�W���W
	gauge.posL.x = 55, gauge.posL.y = 980;
	gauge.posR.x = gauge.posL.x + 490 * ( hp / maxHp ), gauge.posR.y = 1015;
	gauge.prevPosL = gauge.posL;
	gauge.prevPosR = gauge.posR;

	// �_���[�W�pHp�Q�[�W���W
	damageGauge.hp = data->GetPlayer()->GetHitpoint();
	damageGauge.posL = gauge.posL;
	damageGauge.posR = gauge.posR;
	damageGauge.prevPosL = gauge.prevPosL;
	damageGauge.prevPosR = gauge.prevPosR;

	// ���q�G�t�F�N�g������
	for (int i = 0; i < 100; i++)
	{
		int randomX = random.GetRandomInt(gauge.posL.x, gauge.posR.x);
		int randomY = random.GetRandomInt(gauge.posL.y, damageGauge.posR.y);
		int randomSpeed = random.GetRandomInt(PIXEL_MOVE_SPEED_MIN, PIXEL_MOVE_SPEED_MAX);

		hpPixel[i].pos = VGet(randomX, randomY, 0);
		hpPixel[i].speed = randomSpeed;
		hpPixel[i].exist = true;
	}
	
}

void UiHitPoint::Update()
{	
	UpdateValue();

	if (damageGauge.hp >= data->GetPlayer()->GetHitpoint())
	{
		//VibrateUi();
		DecreaseHitPoint();
	}
	else
	{
		vibrateTimer->Reset();
	}

	CreateHpGaugePixel();
	MoveGaugePixel();
}

void UiHitPoint::Draw()
{
	float hp = data->GetPlayer()->GetHitpoint();
	float maxHp = data->GetPlayer()->GetMaxHitpoint();
	float size = imageMgr.GetImageSize(ImageType::PlayerHpGauge);

	gauge.posR.x = gauge.posL.x + 490 * (hp / maxHp);
	damageGauge.posR.x = damageGauge.posL.x + 490 * (damageGauge.hp / maxHp);

	// �_���[�W���̒x�������p��HitPoint
	DrawBox(damageGauge.posL.x, damageGauge.posL.y, damageGauge.posR.x, damageGauge.posR.y, RED, TRUE);
	// �v���C���[��HitPoint��\��
	DrawBox(gauge.posL.x, gauge.posL.y, gauge.posR.x, gauge.posR.y, GREEN, TRUE);
	
	// �Q�[�W�s�N�Z���`��
	for (int i = 0; i < 100; ++i)
	{
		// ���݂��Ȃ��Ȃ�`�悵�Ȃ�
		if (hpPixel[i].exist)
		{
			DrawCircle(hpPixel[i].pos.x, hpPixel[i].pos.y, PIXEL_RADIUS, WHITE, TRUE);
		}
	}
	
	// HitPoint�Q�[�W�g�\��
	DrawRotaGraph(param.pos.x, param.pos.y, size, 0.0f, param.handle, TRUE);
}

void UiHitPoint::UpdateValue()
{


	// 
	if (param.pos != param.prevPos)
	{
		// Ui���W
		param.pos = param.prevPos;
		// �Q�[�W���W
		gauge.posL = gauge.prevPosL;
		gauge.posR = gauge.prevPosR;
		damageGauge.posL = damageGauge.prevPosL;
		damageGauge.posR = damageGauge.prevPosR;
	}

	// Ui���W
	param.prevPos = param.pos;
	// �Q�[�W���W
	gauge.prevPosL = gauge.posL;
	gauge.prevPosR = gauge.posR;
}

void UiHitPoint::VibrateUi()
{
	vibrateTimer->Update(deltaTime.GetDeltaTime());

	if (!vibrateTimer->IsTimeout())
	{
		int randomX = random.GetRandomInt(1, VIBRATE_UI.x);
		int randomY = random.GetRandomInt(1, VIBRATE_UI.y);

		param.pos = VAdd(param.pos, VGet(randomX, randomY, 0));
		gauge.posL = VAdd(gauge.posL, VGet(randomX, randomY, 0));
		gauge.posR = VAdd(gauge.posR, VGet(randomX, randomY, 0));
		damageGauge.posL = gauge.posL;
		damageGauge.posR = gauge.posR;
	}
}

void UiHitPoint::DecreaseHitPoint()
{
	deferredHpTimer->Update(deltaTime.GetDeltaTime());

	// ���݂�Hitpoint�ɂȂ�܂Ō�������
	if (deferredHpTimer->IsTimeout())
	{
		damageGauge.hp -= DECREASE_HITPOINT * deltaTime.GetDeltaTime();
	}
}

void UiHitPoint::CreateHpGaugePixel()
{
	int randomY;
	int randomSpeed;
	
	for (int i = 0; i < 100; i++)
	{
		// ���݂��Ȃ��ꍇ��������
		if (!hpPixel[i].exist)
		{
			// �����ʒu�ݒ�
			randomY = random.GetRandomInt(gauge.posL.y, gauge.posR.y);
			// �ړ����x�ݒ�
			randomSpeed = random.GetRandomInt(PIXEL_MOVE_SPEED_MIN, PIXEL_MOVE_SPEED_MAX);

			hpPixel[i].pos.x = gauge.posL.x;
			hpPixel[i].pos.y = randomY;
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
