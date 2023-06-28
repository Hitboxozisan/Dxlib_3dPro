#include "common.h"
#include "EnemyBulletManager.h"
#include "Bullet.h"

EnemyBulletManager::EnemyBulletManager()
{
	Initialize();
}

EnemyBulletManager::~EnemyBulletManager()
{
}

void EnemyBulletManager::Initialize()
{
	// サイズ分弾を確保
	for (int i = 0; i < BULLET_POOL_SIZE; i++)
	{
		Bullet* bullet = new Bullet(CollisionTag::EnemyBullet);
		bullets.push_back(bullet);
	}
}

void EnemyBulletManager::Update()
{
	for (auto bullet : bullets)
	{
		bullet->Update();
	}
}

void EnemyBulletManager::Draw()
{
	for (auto bullet : bullets)
	{
		if (bullet->IsExist())
		{
			bullet->Draw();
		}
	}
}

void EnemyBulletManager::CreateBullet(VECTOR pos, VECTOR dir, float shotSpeed, ModelType mt)
{
	for (auto bullet : bullets)
	{
		// 生成した弾の中から使用可能な弾がないかチェック
		bullet = GetUnUseBullet();
		// 使用可能な弾がない場合は新たに生成
		if (bullet == nullptr)
		{
			bullets.push_back(new Bullet(CollisionTag::EnemyBullet));
			bullets.back()->Initialize(mt);
			bullets.back()->Create(pos, dir, shotSpeed);
			break;
		}
		else
		{
			bullet->Initialize(mt);
			bullet->Create(pos, dir, shotSpeed);
			break;
		}
	}
}

/// <summary>
/// 使用可能な弾あるか
/// </summary>
/// <returns></returns>
Bullet* EnemyBulletManager::GetUnUseBullet()
{
	for (auto bullet : bullets)
	{
		if (!bullet->IsExist())
		{
			return bullet;
		}
	}
	return nullptr;
}
