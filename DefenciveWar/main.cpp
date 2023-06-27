#include "common.h"
#include "SceneManager.h"
#include "DeltaTime.h"
#include "Singleton.h"
#include "Font.h"
#include "ModelManager.h"
#include "KeyManager.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// TRUE�ɂ����FPS���}���ɗ�����\������
	ChangeWindowMode(FALSE);

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	SetWaitVSyncFlag(TRUE);
	SetUseLighting(TRUE);
	// DirectX11���g�p����
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// �t���X�N���[���A���`�G�C���A�X��ݒ�
	SetFullSceneAntiAliasingMode(4, 2);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//Effekseer������������
	//�����͉�ʂɕ\������ő�p�[�e�B�N����
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//DxLib_Init�֐��̑O�ɒu����FPS��������
	SetDrawScreen(DX_SCREEN_BACK);

	// Effekseer����������

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	// Effekseer��2D�`��̐ݒ������B
	//Effekseer_Set2DSetting(SCREEN_WIDTH, SCREEN_HEIGHT);
	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);
	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	SetWriteZBuffer3D(TRUE);

	class SceneManager& sceneMgr = Singleton<SceneManager>::GetInstance();
	class DeltaTime& deltaTime = Singleton<DeltaTime>::GetInstance();
	class Font& font = Singleton<Font>::GetInstance();
	class ModelManager& modelMgr = Singleton<ModelManager>::GetInstance();
	class KeyManager& key = Singleton<KeyManager>::GetInstance();

	sceneMgr.Initialize();

	deltaTime.SetCount();
	font.SetFont("Molot", 100, 1, DX_FONTTYPE_ANTIALIASING);
	key.CheckSetPad();
	
	//int nowCount, prevCount;
	//nowCount = prevCount = GetNowCount();

	// ���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//deltaTime�̌v��
		//float deltaTime;
		//nowCount = GetNowCount();
		//deltaTime = (nowCount - prevCount) / 1000.0f;

		deltaTime.InstrumentationDeltaTime();

		key.Update();

		sceneMgr.Update();

		sceneMgr.Draw();

		//prevCount = nowCount;
	}

	// Effekseer���I������
	Effkseer_End();

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}