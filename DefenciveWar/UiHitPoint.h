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
	const int	PIXEL_MOVE_SPEED_MAX = 100;		// HitPoint�Q�[�W�ő�ړ����x
	const int	PIXEL_MOVE_SPEED_MIN = 50;		// HitPoint�Q�[�W�ŏ��ړ����x
	const int	PIXEL_RADIUS = 1;
	const float DECREASE_HITPOINT = 50.0f;		// HitPoint������
	const float VIBRATE_TIME = 0.3f;			// �U������
	const float DEFERRED_TIME = 0.5f;			// ��������܂ł̎���

	void UpdateValue();						// �e��l���X�V����
	void VibrateUi();						// Ui��U��������
	void DecreaseHitPoint();				// HitPoint������������
	void CreateHpGaugePixel();				// HitPoint�Q�[�W�G�t�F�N�g�𐶐�
	void MoveGaugePixel();					// ���q�̈ړ�����

	// �Q�[�W��̗��q�G�t�F�N�g
	struct HitpointEffect
	{
		VECTOR pos;				// ���q�ʒu
		VECTOR createPos;		// �����ʒu
		int speed;				// �ړ����x
		bool exist;				// ���݂��Ă��邩
	};
	
	struct HitpointGauge
	{
		// �Q�[�W�E�����_
		VECTOR posR;
		VECTOR prevPosR;
		// �Q�[�W���㒸�_
		VECTOR posL;
		VECTOR prevPosL;
	};
	
	struct SecondHitPointGauge
	{
		// �x��Č�������p��Hitpoint
		int hp;
		// �Q�[�W�E�����_
		VECTOR posR;
		VECTOR prevPosR;
		// �Q�[�W���㒸�_
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

