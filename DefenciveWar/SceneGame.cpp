#include "SceneGame.h"
#include "Singleton.h"
#include "Camera.h"
#include "Player.h"
#include "Ground.h"
#include "EffectManager.h"
#include "BulletManager.h"
#include "KeyManager.h"
#include "Font.h"
#include "UiManager.h"
#include "BehaviorTree.h"
#include "BossEnemy.h"
#include "HitChacker.h"
#include "ObjectData.h"
#include "UiManager.h"

SceneGame::SceneGame(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,camera(Singleton<Camera>::GetInstance())
	,effectMgr(Singleton<EffectManager>::GetInstance())
	,bulletMgr(Singleton<BulletManager>::GetInstance())
	,key(Singleton<KeyManager>::GetInstance())
	,font(Singleton<Font>::GetInstance())
	,uiMgr(Singleton<UiManager>::GetInstance())
	,collideMgr(Singleton<HitChacker>::GetInstance())
	,player(new Player(CollisionTag::Player))
	,ground(new Ground())
	,boss(new BossEnemy(CollisionTag::Enemy, player))
	,state(State::Game)
	
{
	uiMgr.CreateUi(this);
}

SceneGame::~SceneGame()
{
}

void SceneGame::Initialize()
{
	player->Initialize();
	ground->Initialize();
	boss->Initialize();
	uiMgr.Initialize();
}

void SceneGame::Finalize()
{
}

void SceneGame::Activate()
{
	camera.Activate();
}

void SceneGame::Deactivate()
{
}

void SceneGame::Update()
{
	PauseScene();
	// ポーズ画面中は処理しない
	if (state == State::Paused)
	{
		return;
	}

	camera.FollowUpPlayer(player->GetPos());
	player->Update();
	boss->Update();

	// 当たり判定処理
	collideMgr.Update();
	uiMgr.Update();
	effectMgr.Update(player->GetPos());
	bulletMgr.Update();
}

void SceneGame::Draw()
{
	// 画面更新処理
	ClearDrawScreen();

	ground->Draw();
	bulletMgr.Draw();
	player->Draw();
	boss->Draw();
	effectMgr.Draw();
	collideMgr.Draw();
	uiMgr.Draw();

	// ポーズ画面中は "PAUSED" を表示する
	if (state == State::Paused)
	{
		DrawFormatStringToHandle(850, 540, WHITE, font.GetFont(), "PAUSED");
	}

	ScreenFlip();
}

/// <summary>
/// ポーズ画面処理
/// </summary>
void SceneGame::PauseScene()
{
	// ボタンを押したらポーズ画面に移行する
	if (key.IsCheckButtonJustPressed(Pad::Player1, XINPUT_BUTTON_START))
	{
		if (state == State::Paused)
		{
			state = State::Game;
		}
		else if (state != State::Paused)
		{
			state = State::Paused;
		}
	}

}
