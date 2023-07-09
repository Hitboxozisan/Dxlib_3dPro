#pragma once

#include "ModelTypeData.h"

/// <summary>
/// 弾を管理・生成するクラス（プレイヤー用）
/// シングルトン
/// 本来は全てのオブジェクトで統一したいが接触判定の関係上、プレイヤーとエネミー用で分ける
/// </summary>
class EnemyBulletManager
{
public:
	EnemyBulletManager();
	~EnemyBulletManager();

	void Initialize();
	void Update();
	void Draw();

	void CreateBullet(VECTOR pos, VECTOR dir, float shotSpeed, ModelType mt);
	void CreateBulletShotGun(VECTOR actorPos, VECTOR actorDir, float shotSpeed, ModelType mt);
	bool IsHitPlayer();
	
	class Bullet* GetUnUseBullet();

private:
	const int BULLET_POOL_SIZE = 10;		// 事前に作っておく弾の数

	std::vector<Bullet*> bullets;
};

