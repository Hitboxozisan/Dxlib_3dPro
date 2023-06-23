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
	// �|�[�Y��ʒ��͏������Ȃ�
	if (state == State::Paused)
	{
		return;
	}

	camera.FollowUpPlayer(player->GetPos());
	player->Update();
	boss->Update();

	// �����蔻�菈��
	collideMgr.Update();
	uiMgr.Update();
	effectMgr.Update(player->GetPos());
	bulletMgr.Update();
}

void SceneGame::Draw()
{
	// ��ʍX�V����
	ClearDrawScreen();

	ground->Draw();
	bulletMgr.Draw();
	player->Draw();
	boss->Draw();
	effectMgr.Draw();
	collideMgr.Draw();
	uiMgr.Draw();

	// �|�[�Y��ʒ��� "PAUSED" ��\������
	if (state == State::Paused)
	{
		DrawFormatStringToHandle(850, 540, WHITE, font.GetFont(), "PAUSED");
	}

	ScreenFlip();
}

/// <summary>
/// �|�[�Y��ʏ���
/// </summary>
void SceneGame::PauseScene()
{
	// �{�^������������|�[�Y��ʂɈڍs����
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
