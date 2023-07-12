#pragma once

#include "SceneBase.h"

class SceneGame final : public SceneBase
{
public:
	SceneGame(SceneManager* const sceneManager);
	~SceneGame();

	// �Q�[���V�[���̏��
	enum class State
	{
		Start,
		Game,
		GameOver,
		Result,
		Paused,
	};

	void Initialize();	//����������
	void Finalize();	//�I������
	void Activate();	//����������
	void Deactivate();	//�񊈐�������
	void Update();		//�X�V����
	void Draw();		//�`�揈��

	class Player* GetPlayer() { return player; }
	class BossEnemy* GetBossEnemy() { return boss; }

private:
	const float FINISH_GAME_WAIT_TIME = 1.0f;	// ���S���̒�~����

	State state;

	class Camera& camera;
	class EffectManager& effectMgr;
	class BulletManager& bulletMgr;
	class EnemyBulletManager& enemyBulletMgr;
	class KeyManager& key;
	class Font& font;
	class UiManager& uiMgr;
	class HitChacker& collideMgr;
	class DeltaTime& deltaTime;
		  Player* player;
	class Ground* ground;
		  BossEnemy* boss;
	class Timer* waitTimer;						// ���S���̃Q�[�����~������^�C�}�[

	void PauseScene();
};

