#include "common.h"
#include "BulletManager.h"
#include "Bullet.h"

BulletManager::BulletManager()
{
	Initialize();
}

BulletManager::~BulletManager()
{
}

void BulletManager::Initialize()
{
	// サイズ分弾を確保
	for (int i = 0; i < BULLET_POOL_SIZE; i++)
	{
		Bullet* bullet = new Bullet(CollisionTag::PlayerBullet);
		bullets.push_back(bullet);
	}
}

void BulletManager::Update()
{
	for (auto bullet : bullets)
	{
		if (bullet->IsExist())
		{
			bullet->Update();
		}
	}
}

void BulletManager::Draw()
{
	for (auto bullet : bullets)
	{
		if (bullet->IsExist())
		{
			bullet->Draw();
		}
	}
}

void BulletManager::CreateBullet(VECTOR pos, VECTOR dir, float shotSpeed, ModelType mt)
{
	for (auto bullet : bullets)
	{
		// 生成した弾の中から使用可能な弾がないかチェック
		bullet = GetUnUseBullet();
		// 使用可能な弾がない場合は新たに生成
		if (bullet == nullptr)
		{
			bullets.push_back(new Bullet(CollisionTag::PlayerBullet));
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
Bullet* BulletManager::GetUnUseBullet()
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
