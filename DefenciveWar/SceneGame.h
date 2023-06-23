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

	State state;

	class Camera& camera;
	class EffectManager& effectMgr;
	class BulletManager& bulletMgr;
	class KeyManager& key;
	class Font& font;
	class UiManager& uiMgr;
	class HitChacker& collideMgr;
		  Player* player;
	class Ground* ground;
		  BossEnemy* boss;

	void PauseScene();
};

