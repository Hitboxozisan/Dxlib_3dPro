#pragma once

/// <summary>
/// �X�N���[���ѕ`��N���X
/// </summary>
class ScreenBand
{
public:
	ScreenBand();
	~ScreenBand();

	void Initialize();
	void Finalize();
	void Activate();
	void ActivateGameStart();		// �Q�[���J�n���̊���������
	void deactivate();
	void Draw();

	void MoveStopPosition();		// ��~�ʒu�܂ňړ�
	bool SceneChange();				// �Q�[���J�n���̉��o
	bool OpenScreenBand();			// �㉺�т���ʒ[�܂ňړ�

private:
	enum Image
	{
		UPPER_BAND,
		UNDER_BAND,

		BAND_AMOUNT
	};

	const VECTOR INITIALIZE_POSITION_UPPER		 = VGet(0.0f, -540.0f, 0.0f);					// ��я����ʒu
	const VECTOR INITIALIZE_POSITION_UNDER		 = VGet(0.0f, SCREEN_HEIGHT, 0.0f);				// ���я����ʒu
	const VECTOR INITIALIZE_START_POSITION_UPPER = VGet(0.0f, 0.0f, 0.0f);						// ��уQ�[���J�n�����ʒu
	const VECTOR INITIALIZE_START_POSITION_UNDER = VGet(0.0f, 540.0f, 0.0f);					// ���уQ�[���J�n�����ʒu
	const float  POSITION_STOP_UPPER_BAND		 = -360.0f;										// ��ђ�~�ʒu
	const float  POSITION_STOP_UNDER_BAND		 = static_cast<float>(SCREEN_HEIGHT - 180);		// ���ђ�~�ʒu
	const float  POSITION_STOP_CENTER			 = 0.0f;										// ��ʒ����ʒu

	int imageHandle[BAND_AMOUNT];
	VECTOR position[BAND_AMOUNT];

};

