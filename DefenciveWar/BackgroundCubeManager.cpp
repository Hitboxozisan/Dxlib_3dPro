#include "common.h"
#include "BackgroundCubeManager.h"
#include "BackgroundCube.h"
#include "Singleton.h"
#include "Random.h"

BackgroundCubeManager::BackgroundCubeManager(ModelType mt)
	:random(Singleton<Random>::GetInstance())
{
	Initialize(mt);
}

BackgroundCubeManager::~BackgroundCubeManager()
{
}

void BackgroundCubeManager::Initialize(ModelType mt)
{
	for (int i = 0 ; i < CUBE_POOL_SIZE; i++)
	{
		BackgroundCube* cube = new BackgroundCube(CollisionTag::BgCube, mt);
		cubes.push_back(cube);
	}
}

void BackgroundCubeManager::Update()
{
	for (auto cube : cubes)
	{
		float randPosY = random.GetRandomFloat(100, 200);
		randPosY = -randPosY;
		
		float randPosZ = random.GetRandomFloat(0, FIELD_POSITION_NORTH + -FIELD_POSITION_SOUTH);
		randPosZ += FIELD_POSITION_SOUTH;

		VECTOR pos = VGet(FIELD_POSITION_EAST, randPosY, randPosZ);
		VECTOR dir = VGet(0, 1, 0);
		float moveSpeed = random.GetRandomFloat(40, 70);

		if (cube->IsExist())
		{
			cube->Update();
		}
		// ��ʊO�ɏo���ꍇ�͐V���ɐ�������
		else
		{
			cube->Initialize();
			cube->Create(pos, dir, moveSpeed);
		}

	}
}

void BackgroundCubeManager::Draw()
{
	for (auto cube : cubes)
	{
		if (cube->IsExist())
		{
			cube->Draw();
		}
	}
}

/// <summary>
/// �L���[�u�̐������s��
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="moveSpeed"></param>
void BackgroundCubeManager::CreateCube()
{
	float randPosY = random.GetRandomFloat(-50, -100);
	float randPosZ = random.GetRandomFloat(0, SCREEN_HEIGHT);
	VECTOR pos = VGet(SCREEN_WIDTH, randPosY, randPosZ);
	VECTOR dir = VGet(0, 1, 0);
	float moveSpeed = random.GetRandomFloat(10, 50);

	for (auto cube : cubes)
	{
		// ��ʊO�ɏo���L���[�u���Ȃ����`�F�b�N
		if (!cube->IsExist())
		{
			// �V���ɐ���
			cube->Initialize();
			cube->Create(pos, dir, moveSpeed);
		}
	}
}
