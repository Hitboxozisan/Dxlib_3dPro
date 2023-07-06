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
	// �T�C�Y���e���m��
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

/// <summary>
/// �e�̐����i�ʏ�j
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="shotSpeed"></param>
/// <param name="mt"></param>
void EnemyBulletManager::CreateBullet(VECTOR pos, VECTOR dir, float shotSpeed, ModelType mt)
{
	for (auto bullet : bullets)
	{
		// ���������e�̒�����g�p�\�Ȓe���Ȃ����`�F�b�N
		bullet = GetUnUseBullet();
		// �g�p�\�Ȓe���Ȃ��ꍇ�͐V���ɐ���
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
/// �e�̐����i�U�e�j
/// </summary>
/// <param name="centerPos"></param>
/// <param name="centerDir"></param>
/// <param name="shotSpeed"></param>
/// <param name="mt"></param>
void EnemyBulletManager::CreateBulletShotGun(VECTOR actorPos, VECTOR actorDir, float shotSpeed, ModelType mt)
{
	MATRIX matrix;

	VECTOR centerPos = VAdd(actorPos, VScale(actorDir, 50.0f));

	matrix = MGetRotY(DX_PI_F / 15.0f);
	VECTOR rightDir = VTransform(actorDir, matrix);
	VECTOR rightPos = VAdd(actorPos, VScale(rightDir, 50.0f));

	matrix = MGetRotY(DX_PI_F / -15.0f);
	VECTOR leftDir = VTransform(actorDir, matrix);
	VECTOR leftPos = VAdd(actorPos, VScale(leftDir, 50.0f));

	// 3�����˂���
	CreateBullet(centerPos, actorDir, shotSpeed, mt);
	CreateBullet(rightPos, rightDir, shotSpeed, mt);
	CreateBullet(leftPos, leftDir, shotSpeed, mt);
}

/// <summary>
/// �g�p�\�Ȓe���邩
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
