#include "common.h"
#include "SceneManager.h"

#include "SceneTitle.h"
#include "SceneGame.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
	:eachScenes()
	,currentPointer(nullptr)
	,currentScene()
	,nextScene()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneManager::Initialize()
{
	eachScenes[TITLE] = new SceneTitle(this);
	eachScenes[GAME_MAIN] = new SceneGame(this);
	//eachScenes[RESULT] = new Result(this);

	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScenes[i]->Initialize();
	}

	// 本来はTITLE
	currentScene = nextScene = TITLE;
#if DEBUG
	currentScene = nextScene = GAME_MAIN;
#endif

	currentPointer = eachScenes[currentScene];
	currentPointer->Activate();
}

void SceneManager::Finalize()
{
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScenes[i]->Finalize();
		delete eachScenes[i];
		eachScenes[i] = nullptr;
	}
}

void SceneManager::Update()
{
	if (currentScene != nextScene)
	{
		ChangeScene();		//次のシーン
	}

	if (currentPointer != nullptr)
	{
		currentPointer->Update();	//現在のシーンの更新処理
	}
}

void SceneManager::Draw()
{
	if (currentPointer != nullptr)
	{
		currentPointer->Draw();		//現在のシーンの描画処理
	}
}

void SceneManager::SetNextScene(Scene next)
{
	nextScene = next;
}

void SceneManager::ChangeScene()
{
	if (nextScene == END)
	{
		return;
	}


	currentPointer->Deactivate();
	currentPointer = eachScenes[nextScene];
	currentScene = nextScene;
	currentPointer->Activate();
}
