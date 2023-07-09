#pragma once

#include "ModelTypeData.h"

/// <summary>
/// �e���Ǘ��E��������N���X�i�v���C���[�p�j
/// �V���O���g��
/// �{���͑S�ẴI�u�W�F�N�g�œ��ꂵ�������ڐG����̊֌W��A�v���C���[�ƃG�l�~�[�p�ŕ�����
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
	const int BULLET_POOL_SIZE = 10;		// ���O�ɍ���Ă����e�̐�

	std::vector<Bullet*> bullets;
};

