#include "common.h"
#include "ScreenBand.h"
#include "GameDefine.h"

ScreenBand::ScreenBand()
{
	// 処理なし
}

ScreenBand::~ScreenBand()
{
	// 処理なし
}


//---------------------------------------------
// 初期化処理
//---------------------------------------------
void ScreenBand::Initialize()
{
	for (int i = 0; i < BAND_AMOUNT; ++i)
	{
		imageHandle[i] = LoadGraph("Data/Image/Band.png");
		if (imageHandle[i] < 0)
		{
			printfDx("画像読み込みに失敗_Band[%d]", i);
		}
	}

	position[0] = INITIALIZE_POSITION_UPPER;
	position[1] = INITIALIZE_POSITION_UNDER;
}


//---------------------------------------------
// 終了処理
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
// 活性化処理
//---------------------------------------------
void ScreenBand::Activate()
{
	position[0] = INITIALIZE_POSITION_UPPER;
	position[1] = INITIALIZE_POSITION_UNDER;
}

/// <summary>
/// ゲーム開始時の活性化処理
/// </summary>
void ScreenBand::ActivateGameStart()
{
	position[0] = INITIALIZE_START_POSITION_UPPER;
	position[1] = INITIALIZE_START_POSITION_UNDER;
}


//---------------------------------------------
// 非活性化処理
//---------------------------------------------
void ScreenBand::deactivate()
{
}


//---------------------------------------------
// 描画処理
//---------------------------------------------
void ScreenBand::Draw()
{
	for (int i = 0; i < BAND_AMOUNT; ++i)
	{
		DrawGraph(position[i].x, position[i].y, imageHandle[i], TRUE);
	}
}


//---------------------------------------------
// 停止位置まで移動
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
/// 画面中央まで帯を移動
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
/// 上下帯を画面端まで移動
/// </summary>
/// <returns>完了した</returns>
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
