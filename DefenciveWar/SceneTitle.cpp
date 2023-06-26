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
/// コンストラクタ
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
	// デモ映像の読み込み
	movieHandle = LoadGraph(MovieData::FILE_PATH[MovieType::Demo].c_str());
	// タイトルロゴ画像読み込み
	titleImageHandle = imageMgr.GetImage(ImageType::TitleLogo);

	// 画面帯管理インスタンス生成
	screenBand = new ScreenBand;
	screenBand->Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
SceneTitle::~SceneTitle()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneTitle::Initialize()
{
	soundMgr.SetBgmVolume(5);
	soundMgr.SetSeVolume(8);

	
}

/// <summary>
/// 終了処理
/// </summary>
void SceneTitle::Finalize()
{
}

/// <summary>
/// 活性化処理
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
/// 非活性化処理
/// </summary>
void SceneTitle::Deactivate()
{
	// 動画を停止する
	PauseMovieToGraph(movieHandle);
}

/// <summary>
/// 更新処理
/// </summary>
void SceneTitle::Update()
{
	// 項目選択
	SelectMode();

	// 項目選択を行った場合サウンドを再生する
	//SoundManager::GetInstance().SetSePlayFlag(SoundManager::Se::SELECT);

	// ゲームを開始した場合画面を暗転させる
	// 画面が暗転したらシーンを切り替える
	if (state == State::START && screenBand->SceneChange())
	{
		PauseMovieToGraph(movieHandle);
		parent->SetNextScene(SceneManager::GAME_MAIN);
		return;
	}

	//++frame;
}

/// <summary>
/// 描画処理
/// </summary>
void SceneTitle::Draw()
{
	// 画面更新処理
	ClearDrawScreen();

	// デモ映像再生終了したら最初に戻る
	if (GetMovieStateToGraph(movieHandle) == 0)
	{
		// 動画再生タイミングを指定
		SeekMovieToGraph(movieHandle, 0);
		//動画を再生できる状態にする
		PlayMovieToGraph(movieHandle);
	}

	// デモ映像を再生する
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, movieHandle, FALSE);

	//タイトル名描画
	DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, titleImageHandle, TRUE);

	// 選択項目の文字を点滅させる
	alpha += alphaAdd;

	if (alpha <= 0 || alpha >= 255)
	{
		alphaAdd = -alphaAdd;
		alpha = prevAlpha;
	}

	prevAlpha = alpha;

	// 選択項目に応じて項目を点滅
	DrawSelectMode();

	// 画面帯描画
	screenBand->Draw();

	ScreenFlip();
}

void SceneTitle::DrawSelectMode()
{

	// 項目に応じて描画を変更
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
	// ゲーム開始処理が複数回発生しないように
	if (state != State::START)
	{
		// ゲームレベルを決定
		SelectLevel();

		// ゲームスタート音を再生
		soundMgr.SetSePlayFlag(SoundManager::PUSH_START);

		// 1フレームで増加するalpha値を増加させる
		alphaAdd *= 10;
		//frame = 0;
		isStartGame = true;

		state = State::START;
	}
}

void SceneTitle::SelectMode()
{
	// 項目選択
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
		// サウンドオプション時は選択音が再生しないようにする
		SelectSound(KEY_INPUT_J);
	}
	if (key.CheckJustPressed(KEY_INPUT_L))
	{
		PushRightButtonState();
		// サウンドオプション時は選択音が再生しないようにする
		SelectSound(KEY_INPUT_L);
	}

	// 決定
	if (key.CheckJustPressed(KEY_INPUT_M))
	{
		PushEnterButoonState();
	}
	// 戻る
	if (key.CheckJustPressed(KEY_INPUT_N))
	{
		PushBackButtonState();
	}
}

void SceneTitle::SelectSound(int keyCode)
{
	int prevBgmVolume = soundMgr.GetBgmVolume();
	int prevSeVolume = soundMgr.GetSeVolume();

	// 増加
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
	// 減少
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

	// ボリュームが変更された場合サンプルボイスを再生
	if (prevBgmVolume != soundMgr.GetBgmVolume() ||
		prevSeVolume != soundMgr.GetSeVolume())
	{
		if (prevSeVolume != soundMgr.GetSeVolume())
		{
			// テストSeを再生する
			//SoundManager::GetInstance().SetSePlayFlag(SoundManager::Se::SOUND_SE_TEST);
		}

	}
}

void SceneTitle::PushUpButtonState()
{
	switch (selectState)
	{
	case SceneTitle::SelectState::START:
		// 何もしない
		break;
	case SceneTitle::SelectState::OPTION:
		selectState = SelectState::START;
		break;
	case SceneTitle::SelectState::NORMAL:
		// 何もしない
		break;
	case SceneTitle::SelectState::HARD:
		// 何もしない
		break;
		//case SceneTitle::SelectState::SOUND_OPTION_ALL:
			//break;
	case SceneTitle::SelectState::SOUND_BGM:
		// 何もしない
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
		// 何もしない
		break;
	case SceneTitle::SelectState::NORMAL:
		// 何もしない
		break;
	case SceneTitle::SelectState::HARD:
		// 何もしない
		break;
		//case SceneTitle::SelectState::SOUND_OPTION_ALL:
			//break;
	case SceneTitle::SelectState::SOUND_BGM:
		selectState = SelectState::SOUND_SE;
		break;
	case SceneTitle::SelectState::SOUND_SE:
		// 何もしない
		break;
	}
}

void SceneTitle::PushRightButtonState()
{
	switch (selectState)
	{
	case SceneTitle::SelectState::START:
		// 何もしない
		break;
	case SceneTitle::SelectState::OPTION:
		// 何もしない
		break;
	case SceneTitle::SelectState::NORMAL:
		selectState = SelectState::HARD;
		break;
	case SceneTitle::SelectState::HARD:
		// 何もしない
		break;
	case SceneTitle::SelectState::SOUND_BGM:
		// "SoundSelect" に記載
		break;
	case SceneTitle::SelectState::SOUND_SE:
		// "SoundSelect" に記載
		break;
	}
}

void SceneTitle::PushLeftButtonState()
{
	switch (selectState)
	{
	case SceneTitle::SelectState::START:
		// 何もしない
		break;
	case SceneTitle::SelectState::OPTION:
		// 何もしない
		break;
	case SceneTitle::SelectState::NORMAL:
		// 何もしない
		break;
	case SceneTitle::SelectState::HARD:
		selectState = SelectState::NORMAL;
		break;
	case SceneTitle::SelectState::SOUND_BGM:
		// "SoundSelect" に記載
		break;
	case SceneTitle::SelectState::SOUND_SE:
		// "SoundSelect" に記載
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
		// 何もしない
		break;
	case SceneTitle::SelectState::SOUND_SE:
		// 何もしない
		break;
	}
}

void SceneTitle::PushBackButtonState()
{
	switch (selectState)
	{
	case SceneTitle::SelectState::START:
		// 何もしない
		break;
	case SceneTitle::SelectState::OPTION:
		// 何もしない
		break;
	case SceneTitle::SelectState::NORMAL:
		selectState = SelectState::START;
		break;
	case SceneTitle::SelectState::HARD:
		// 何もしない
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
