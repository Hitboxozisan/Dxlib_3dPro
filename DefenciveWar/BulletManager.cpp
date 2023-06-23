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
	// �T�C�Y���e���m��
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
		}
			bullet->Draw();
	}
}

void BulletManager::CreateBullet(VECTOR pos, VECTOR dir, float shotSpeed, ModelType mt)
{
	for (auto bullet : bullets)
	{
		// ���������e�̒�����g�p�\�Ȓe���Ȃ����`�F�b�N
		bullet = GetUnUseBullet();
		// �g�p�\�Ȓe���Ȃ��ꍇ�͐V���ɐ���
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
/// �g�p�\�Ȓe���邩
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
