#pragma once

#include "SceneBase.h"

class SceneGame final : public SceneBase
{
public:
	SceneGame(SceneManager* const sceneManager);
	~SceneGame();

	// ゲームシーンの状態
	enum class State
	{
		Start,
		Game,
		GameOver,
		Result,
		Paused,
	};

	void Initialize();	//初期化処理
	void Finalize();	//終了処理
	void Activate();	//活性化処理
	void Deactivate();	//非活性化処理
	void Update();		//更新処理
	void Draw();		//描画処理

	class Player* GetPlayer() { return player; }
	class BossEnemy* GetBossEnemy() { return boss; }

private:

	State state;

	class Camera& camera;
	class EffectManager& effectMgr;
	class BulletManager& bulletMgr;
	class EnemyBulletManager& enemyBulletMgr;
	class KeyManager& key;
	class Font& font;
	class UiManager& uiMgr;
	class HitChacker& collideMgr;
		  Player* player;
	class Ground* ground;
		  BossEnemy* boss;

	void PauseScene();
};

