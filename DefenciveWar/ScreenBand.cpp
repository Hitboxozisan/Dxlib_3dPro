#include "common.h"
#include "ScreenBand.h"
#include "GameDefine.h"

ScreenBand::ScreenBand()
{
	// �����Ȃ�
}

ScreenBand::~ScreenBand()
{
	// �����Ȃ�
}


//---------------------------------------------
// ����������
//---------------------------------------------
void ScreenBand::Initialize()
{
	for (int i = 0; i < BAND_AMOUNT; ++i)
	{
		imageHandle[i] = LoadGraph("Data/Image/Band.png");
		if (imageHandle[i] < 0)
		{
			printfDx("�摜�ǂݍ��݂Ɏ��s_Band[%d]", i);
		}
	}

	position[0] = INITIALIZE_POSITION_UPPER;
	position[1] = INITIALIZE_POSITION_UNDER;
}


//---------------------------------------------
// �I������
//---------------------------------------------
void ScreenBand::Finalize()
{
	for (int i = 0; i < BAND_AMOUNT; ++i)
	{
		DeleteGraph(imageHandle[i]);
		imageHandle[i] = NULL;
	}
}


//---------------------------------------------
// ����������
//---------------------------------------------
void ScreenBand::Activate()
{
	position[0] = INITIALIZE_POSITION_UPPER;
	position[1] = INITIALIZE_POSITION_UNDER;
}

/// <summary>
/// �Q�[���J�n���̊���������
/// </summary>
void ScreenBand::ActivateGameStart()
{
	position[0] = INITIALIZE_START_POSITION_UPPER;
	position[1] = INITIALIZE_START_POSITION_UNDER;
}


//---------------------------------------------
// �񊈐�������
//---------------------------------------------
void ScreenBand::deactivate()
{
}


//---------------------------------------------
// �`�揈��
//---------------------------------------------
void ScreenBand::Draw()
{
	for (int i = 0; i < BAND_AMOUNT; ++i)
	{
		DrawGraph(position[i].x, position[i].y, imageHandle[i], TRUE);
	}
}


//---------------------------------------------
// ��~�ʒu�܂ňړ�
//---------------------------------------------
void ScreenBand::MoveStopPosition()
{
	if (position[0].y <= POSITION_STOP_UPPER_BAND || position[1].y >= POSITION_STOP_UNDER_BAND)
	{
		position[0].y += 3;
		position[1].y -= 3;
	}
}

/// <summary>
/// ��ʒ����܂őт��ړ�
/// </summary>
/// <returns></returns>
bool ScreenBand::SceneChange()
{

	if (position[0].y + 3 <= POSITION_STOP_CENTER)
	{
		position[0].y += 3;
		position[1].y -= 3;

		return false;
	}
	
	return true;
}

/// <summary>
/// �㉺�т���ʒ[�܂ňړ�
/// </summary>
/// <returns>��������</returns>
bool ScreenBand::OpenScreenBand()
{
	if (position[0].y + 3 >= INITIALIZE_POSITION_UPPER.y)
	{
		position[0].y -= 3;
		position[1].y += 3;

		return true;
	}
	
	return false;
}
