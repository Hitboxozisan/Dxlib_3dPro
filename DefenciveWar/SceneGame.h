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
	const float FINISH_GAME_WAIT_TIME = 1.0f;	// 死亡時の停止時間

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
	class Timer* waitTimer;						// 死亡時のゲームを停止させるタイマー

	void PauseScene();
};

