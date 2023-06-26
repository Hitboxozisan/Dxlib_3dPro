#include "common.h"
#include "SceneManager.h"
#include "DeltaTime.h"
#include "Singleton.h"
#include "Font.h"
#include "ModelManager.h"
#include "KeyManager.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// TRUEにするとFPSが急激に落ちる可能性あり
	ChangeWindowMode(TRUE);

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	SetWaitVSyncFlag(TRUE);
	SetUseLighting(TRUE);
	// DirectX11を使用する
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// フルスクリーンアンチエイリアスを設定
	SetFullSceneAntiAliasingMode(4, 2);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//Effekseerを初期化する
	//引数は画面に表示する最大パーティクル数
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//DxLib_Init関数の前に置くとFPSが落ちる
	SetDrawScreen(DX_SCREEN_BACK);

	// Effekseer初期化処理

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	// Effekseerに2D描画の設定をする。
	//Effekseer_Set2DSetting(SCREEN_WIDTH, SCREEN_HEIGHT);
	// Zバッファを有効にする
	SetUseZBuffer3D(TRUE);
	// Zバッファへの書き込みを有効にする。
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

	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//deltaTimeの計測
		//float deltaTime;
		//nowCount = GetNowCount();
		//deltaTime = (nowCount - prevCount) / 1000.0f;

		deltaTime.InstrumentationDeltaTime();

		key.Update();

		sceneMgr.Update();

		sceneMgr.Draw();

		//prevCount = nowCount;
	}

	// Effekseerを終了する
	Effkseer_End();

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}