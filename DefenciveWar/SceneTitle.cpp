#include "common.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "ScreenBand.h"
#include "Singleton.h"
#include "SoundManager.h"
#include "MovieData.h"
#include "Font.h"
#include "KeyManager.h"
#include "ImageManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
SceneTitle::SceneTitle(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	, soundMgr(Singleton<SoundManager>::GetInstance())
	, font(Singleton<Font>::GetInstance())
	, key(Singleton<KeyManager>::GetInstance())
	, imageMgr(Singleton<ImageManager>::GetInstance())
	,state(State::DEMO)
	,selectState(SelectState::START)
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void SceneTitle::Initialize()
{
	soundMgr.SetBgmVolume(5);
	soundMgr.SetSeVolume(8);

	// �f���f���̓ǂݍ���
	movieHandle = LoadGraph(MovieData::FILE_PATH[MovieType::Demo].c_str());
	// �^�C�g�����S�摜�ǂݍ���
	titleImageHandle = imageMgr.GetImage(ImageType::TitleLogo);

	// ��ʑъǗ��C���X�^���X����
	screenBand = new ScreenBand;
	screenBand->Initialize();
}

/// <summary>
/// �I������
/// </summary>
void SceneTitle::Finalize()
{
}

/// <summary>
/// ����������
/// </summary>
void SceneTitle::Activate()
{
	state = State::DEMO;
	selectState = SelectState::START;
	alpha = 255;
	alphaAdd = -3;
	//frame = 0;
	isStartGame = false;

	screenBand->Activate();
}

/// <summary>
/// �񊈐�������
/// </summary>
void SceneTitle::Deactivate()
{
	// ������~����
	PauseMovieToGraph(movieHandle);
}

/// <summary>
/// �X�V����
/// </summary>
void SceneTitle::Update()
{
	// ���ڑI��
	SelectMode();

	// ���ڑI�����s�����ꍇ�T�E���h���Đ�����
	//SoundManager::GetInstance().SetSePlayFlag(SoundManager::Se::SELECT);

	// �Q�[�����J�n�����ꍇ��ʂ��Ó]������
	// ��ʂ��Ó]������V�[����؂�ւ���
	if (state == State::START && screenBand->SceneChange())
	{
		PauseMovieToGraph(movieHandle);
		parent->SetNextScene(SceneManager::GAME_MAIN);
		return;
	}

	//++frame;
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneTitle::Draw()
{
	// ��ʍX�V����
	ClearDrawScreen();

	// �f���f���Đ��I��������ŏ��ɖ߂�
	if (GetMovieStateToGraph(movieHandle) == 0)
	{
		// ����Đ��^�C�~���O���w��
		SeekMovieToGraph(movieHandle, 0);
		//������Đ��ł����Ԃɂ���
		PlayMovieToGraph(movieHandle);
	}

	// �f���f�����Đ�����
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, movieHandle, FALSE);

	//�^�C�g�����`��
	DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, titleImageHandle, TRUE);

	// �I�����ڂ̕�����_�ł�����
	alpha += alphaAdd;

	if (alpha <= 0 || alpha >= 255)
	{
		alphaAdd = -alphaAdd;
		alpha = prevAlpha;
	}

	prevAlpha = alpha;

	// �I�����ڂɉ����č��ڂ�_��
	DrawSelectMode();

	// ��ʑѕ`��
	screenBand->Draw();

	ScreenFlip();
}

void SceneTitle::DrawSelectMode()
{

	// ���ڂɉ����ĕ`���ύX
	switch (selectState)
	{
	case SelectState::START:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawFormatStringToHandle(START_SELECT_POSITION.x, START_SELECT_POSITION.y, WHITE, font.GetFont(), "START");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);

		DrawFormatStringToHandle(OPTION_POSITION.x, OPTION_POSITION.y, WHITE, font.GetFont(), "OPTION");
		break;
	case SelectState::OPTION:
		DrawFormatStringToHandle(START_SELECT_POSITION.x, START_SELECT_POSITION.y, WHITE, font.GetFont(), "START");

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawFormatStringToHandle(OPTION_POSITION.x, OPTION_POSITION.y, WHITE, font.GetFont(), "OPTION");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
		break;
	case SelectState::NORMAL:
		DrawFormatStringToHandle(SELECT_LEVEL_POSITION.x, SELECT_LEVEL_POSITION.y, WHITE, font.GetFont(), "SELECT LEVEL");
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawFormatStringToHandle(SELECT_LEVEL_NORMAL_POSITION.x, SELECT_LEVEL_NORMAL_POSITION.y, WHITE, font.GetFont(), "NORMAL");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
		DrawFormatStringToHandle(SELECT_LEVEL_HARD_POSITION.x, SELECT_LEVEL_HARD_POSITION.y, WHITE, font.GetFont(), "HARD");
		break;
	case SelectState::HARD:
		DrawFormatStringToHandle(SELECT_LEVEL_POSITION.x, SELECT_LEVEL_POSITION.y, WHITE, font.GetFont(), "SELECT LEVEL");
		DrawFormatStringToHandle(SELECT_LEVEL_NORMAL_POSITION.x, SELECT_LEVEL_NORMAL_POSITION.y, WHITE, font.GetFont(), "NORMAL");
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawFormatStringToHandle(SELECT_LEVEL_HARD_POSITION.x, SELECT_LEVEL_HARD_POSITION.y, WHITE, font.GetFont(), "HARD");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
		break;
	case SelectState::SOUND_BGM:
		DrawFormatStringToHandle(SELECT_LEVEL_POSITION.x, SELECT_LEVEL_POSITION.y, WHITE, font.GetFont(), "SOUND OPTION");
		// BGM
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawFormatStringToHandle(SOUND_BGM_POSITION.x, SOUND_BGM_POSITION.y, WHITE, font.GetFont(), "BGM");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
		DrawFormatStringToHandle(SOUND_BGM_VOLUME_POSITION.x, SOUND_BGM_VOLUME_POSITION.y, WHITE, font.GetFont(), "< %d >", soundMgr.GetBgmVolume());
		// SE
		DrawFormatStringToHandle(SOUND_SE_POSITION.x, SOUND_SE_POSITION.y, WHITE, font.GetFont(), "SE");
		DrawFormatStringToHandle(SOUND_SE_VOLUME_POSITION.x, SOUND_SE_VOLUME_POSITION.y, WHITE, font.GetFont(), "< %d >", soundMgr.GetSeVolume());
		break;
	case SelectState::SOUND_SE:
		DrawFormatStringToHandle(SELECT_LEVEL_POSITION.x, SELECT_LEVEL_POSITION.y, WHITE, font.GetFont(), "SOUND OPTION");
		// BGM
		DrawFormatStringToHandle(SOUND_BGM_POSITION.x, SOUND_BGM_POSITION.y, WHITE, font.GetFont(), "BGM");
		DrawFormatStringToHandle(SOUND_BGM_VOLUME_POSITION.x, SOUND_BGM_VOLUME_POSITION.y, WHITE, font.GetFont(), "< %d >", soundMgr.GetBgmVolume());
		// SE
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawFormatStringToHandle(SOUND_SE_POSITION.x, SOUND_SE_POSITION.y, WHITE, font.GetFont(), "SE");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
		DrawFormatStringToHandle(SOUND_SE_VOLUME_POSITION.x, SOUND_SE_VOLUME_POSITION.y, WHITE, font.GetFont(), "< %d >", soundMgr.GetSeVolume());
		break;
	}
}

void SceneTitle::SelectLevel()
{
}

void SceneTitle::StartGame()
{
	// �Q�[���J�n�����������񔭐����Ȃ��悤��
	if (state != State::START)
	{
		// �Q�[�����x��������
		SelectLevel();

		// �Q�[���X�^�[�g�����Đ�
		soundMgr.SetSePlayFlag(SoundManager::PUSH_START);

		// 1�t���[���ő�������alpha�l�𑝉�������
		alphaAdd *= 10;
		//frame = 0;
		isStartGame = true;

		state = State::START;
	}
}

void SceneTitle::SelectMode()
{
	// ���ڑI��
	if (key.CheckJustPressed(KEY_INPUT_I))
	{
		PushUpButtonState();
	}
	if (key.CheckJustPressed(KEY_INPUT_K))
	{
		PushDownButtonState();
	}
	if (key.CheckJustPressed(KEY_INPUT_J))
	{
		PushLeftButtonState();
		// �T�E���h�I�v�V�������͑I�������Đ����Ȃ��悤�ɂ���
		SelectSound(KEY_INPUT_J);
	}
	if (key.CheckJustPressed(KEY_INPUT_L))
	{
		PushRightButtonState();
		// �T�E���h�I�v�V�������͑I�������Đ����Ȃ��悤�ɂ���
		SelectSound(KEY_INPUT_L);
	}

	// ����
	if (key.CheckJustPressed(KEY_INPUT_M))
	{
		PushEnterButoonState();
	}
	// �߂�
	if (key.CheckJustPressed(KEY_INPUT_N))
	{
		PushBackButtonState();
	}
}

void SceneTitle::SelectSound(int keyCode)
{
	int prevBgmVolume = soundMgr.GetBgmVolume();
	int prevSeVolume = soundMgr.GetSeVolume();

	// ����
	if (keyCode == KEY_INPUT_L)
	{
		// BGM
		if (selectState == SelectState::SOUND_BGM && soundMgr.GetBgmVolume() < MAX_VOLUME)
		{
			soundMgr.SetBgmVolume(prevBgmVolume++);
		}
		// SE
		if (selectState == SelectState::SOUND_SE && soundMgr.GetSeVolume() < MAX_VOLUME)
		{
			soundMgr.SetSeVolume(prevSeVolume++);
		}
	}
	// ����
	if (keyCode == KEY_INPUT_J)
	{
		// BGM
		if (selectState == SelectState::SOUND_BGM && soundMgr.GetBgmVolume() > 0.0f)
		{
			soundMgr.SetBgmVolume(prevBgmVolume--);
		}
		// SE
		if (selectState == SelectState::SOUND_SE && soundMgr.GetSeVolume() > 0.0f)
		{
			soundMgr.SetSeVolume(prevSeVolume--);
		}
	}

	// �{�����[�����ύX���ꂽ�ꍇ�T���v���{�C�X���Đ�
	if (prevBgmVolume != soundMgr.GetBgmVolume() ||
		prevSeVolume != soundMgr.GetSeVolume())
	{
		if (prevSeVolume != soundMgr.GetSeVolume())
		{
			// �e�X�gSe���Đ�����
			//SoundManager::GetInstance().SetSePlayFlag(SoundManager::Se::SOUND_SE_TEST);
		}

	}
}

void SceneTitle::PushUpButtonState()
{
	switch (selectState)
	{
	case SceneTitle::SelectState::START:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::OPTION:
		selectState = SelectState::START;
		break;
	case SceneTitle::SelectState::NORMAL:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::HARD:
		// �������Ȃ�
		break;
		//case SceneTitle::SelectState::SOUND_OPTION_ALL:
			//break;
	case SceneTitle::SelectState::SOUND_BGM:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::SOUND_SE:
		selectState = SelectState::SOUND_BGM;
		break;
	}
}

void SceneTitle::PushDownButtonState()
{
	switch (selectState)
	{
	case SceneTitle::SelectState::START:
		selectState = SelectState::OPTION;
		break;
	case SceneTitle::SelectState::OPTION:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::NORMAL:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::HARD:
		// �������Ȃ�
		break;
		//case SceneTitle::SelectState::SOUND_OPTION_ALL:
			//break;
	case SceneTitle::SelectState::SOUND_BGM:
		selectState = SelectState::SOUND_SE;
		break;
	case SceneTitle::SelectState::SOUND_SE:
		// �������Ȃ�
		break;
	}
}

void SceneTitle::PushRightButtonState()
{
	switch (selectState)
	{
	case SceneTitle::SelectState::START:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::OPTION:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::NORMAL:
		selectState = SelectState::HARD;
		break;
	case SceneTitle::SelectState::HARD:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::SOUND_BGM:
		// "SoundSelect" �ɋL��
		break;
	case SceneTitle::SelectState::SOUND_SE:
		// "SoundSelect" �ɋL��
		break;
	}
}

void SceneTitle::PushLeftButtonState()
{
	switch (selectState)
	{
	case SceneTitle::SelectState::START:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::OPTION:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::NORMAL:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::HARD:
		selectState = SelectState::NORMAL;
		break;
	case SceneTitle::SelectState::SOUND_BGM:
		// "SoundSelect" �ɋL��
		break;
	case SceneTitle::SelectState::SOUND_SE:
		// "SoundSelect" �ɋL��
		break;
	}
}

void SceneTitle::PushEnterButoonState()
{
	switch (selectState)
	{
	case SceneTitle::SelectState::START:
		selectState = SelectState::NORMAL;
		break;
	case SceneTitle::SelectState::OPTION:
		selectState = SelectState::SOUND_BGM;
		break;
	case SceneTitle::SelectState::NORMAL:
		StartGame();
		break;
	case SceneTitle::SelectState::HARD:
		StartGame();
		break;
		//case SceneTitle::SelectState::SOUND_OPTION_ALL:
			//break;
	case SceneTitle::SelectState::SOUND_BGM:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::SOUND_SE:
		// �������Ȃ�
		break;
	}
}

void SceneTitle::PushBackButtonState()
{
	switch (selectState)
	{
	case SceneTitle::SelectState::START:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::OPTION:
		// �������Ȃ�
		break;
	case SceneTitle::SelectState::NORMAL:
		selectState = SelectState::START;
		break;
	case SceneTitle::SelectState::HARD:
		// �������Ȃ�
		break;
		//case SceneTitle::SelectState::SOUND_OPTION_ALL:
			//break;
	case SceneTitle::SelectState::SOUND_BGM:
		selectState = SelectState::START;
		break;
	case SceneTitle::SelectState::SOUND_SE:
		selectState = SelectState::START;
		break;
	}
}
