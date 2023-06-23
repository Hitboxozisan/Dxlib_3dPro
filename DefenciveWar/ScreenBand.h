#pragma once

/// <summary>
/// スクリーン帯描画クラス
/// </summary>
class ScreenBand
{
public:
	ScreenBand();
	~ScreenBand();

	void Initialize();
	void Finalize();
	void Activate();
	void ActivateGameStart();		// ゲーム開始時の活性化処理
	void deactivate();
	void Draw();

	void MoveStopPosition();		// 停止位置まで移動
	bool SceneChange();				// ゲーム開始時の演出
	bool OpenScreenBand();			// 上下帯を画面端まで移動

private:
	enum Image
	{
		UPPER_BAND,
		UNDER_BAND,

		BAND_AMOUNT
	};

	const VECTOR INITIALIZE_POSITION_UPPER		 = VGet(0.0f, -540.0f, 0.0f);					// 上帯初期位置
	const VECTOR INITIALIZE_POSITION_UNDER		 = VGet(0.0f, SCREEN_HEIGHT, 0.0f);				// 下帯初期位置
	const VECTOR INITIALIZE_START_POSITION_UPPER = VGet(0.0f, 0.0f, 0.0f);						// 上帯ゲーム開始初期位置
	const VECTOR INITIALIZE_START_POSITION_UNDER = VGet(0.0f, 540.0f, 0.0f);					// 下帯ゲーム開始初期位置
	const float  POSITION_STOP_UPPER_BAND		 = -360.0f;										// 上帯停止位置
	const float  POSITION_STOP_UNDER_BAND		 = static_cast<float>(SCREEN_HEIGHT - 180);		// 下帯停止位置
	const float  POSITION_STOP_CENTER			 = 0.0f;										// 画面中央位置

	int imageHandle[BAND_AMOUNT];
	VECTOR position[BAND_AMOUNT];

};

