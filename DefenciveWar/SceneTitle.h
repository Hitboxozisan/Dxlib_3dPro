#pragma once

#include "SceneBase.h"

/// <summary>
/// タイトルシーン
/// </summary>
class SceneTitle final : public SceneBase
{
public:
	SceneTitle(SceneManager* const sceneManager);
	~SceneTitle();

	enum class State
	{
		DEMO,
		START,
	};

	enum class SelectState
	{
		START,
		OPTION,
		NORMAL,
		HARD,
		SOUND_BGM,
		SOUND_SE,
	};

	void Initialize();	//初期化処理
	void Finalize();	//終了処理
	void Activate();	//活性化処理
	void Deactivate();	//非活性化処理
	void Update();		//更新処理
	void Draw();		//描画処理

private:
	// 選択項目描画位置
	const VECTOR START_SELECT_POSITION = VGet(500.0f, 600.0f, 0.0f);
	const VECTOR OPTION_POSITION = VGet(500.0f, 800.0f, 0.0f);
	const VECTOR SELECT_LEVEL_POSITION = VGet(400.0f, 600.0f, 0.0f);
	const VECTOR SELECT_LEVEL_NORMAL_POSITION = VGet(400.0f, 800.0f, 0.0f);
	const VECTOR SELECT_LEVEL_HARD_POSITION = VGet(1000.0f, 800.0f, 0.0f);
	const VECTOR SOUND_OPTION_POSITION = VGet(400.0f, 600.0f, 0.0f);
	const VECTOR SOUND_BGM_POSITION = VGet(400.0f, 750.0f, 0.0f);
	const VECTOR SOUND_SE_POSITION = VGet(400.0f, 850.0f, 0.0f);
	const VECTOR SOUND_BGM_VOLUME_POSITION = VGet(800.0f, 750.0f, 0.0f);
	const VECTOR SOUND_SE_VOLUME_POSITION = VGet(800.0f, 850.0f, 0.0f);

	static const int BLINKING_TIMES;				// ゲーム開始時のアイコン点滅回数
	const int MAX_VOLUME = 10;						// 最大音量

	class ScreenBand* screenBand;
	class SoundManager& soundMgr;
	class Font& font;
	class KeyManager& key;
	class ImageManager& imageMgr;

	State state;
	SelectState selectState;

	void DrawSelectMode();							// 選択項目を描画
	void SelectLevel();								// ゲーム難易度を選択
	void StartGame();								// ゲームを開始する
	void SelectMode();								// 項目を選択
	void SelectSound(int keyCode);					// ゲームサウンドを設定

	// 各ボタンを押した際の項目遷移
	void PushUpButtonState();
	void PushDownButtonState();
	void PushRightButtonState();
	void PushLeftButtonState();
	void PushEnterButoonState();
	void PushBackButtonState();

	int movieHandle;
	int titleImageHandle;
	int alpha;
	int prevAlpha;
	int alphaAdd;
	bool isStartGame;			// ゲームを開始したか
};

