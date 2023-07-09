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
		// キューブの高さ
		float randPosY = random.GetRandomFloat(200, 300);
		randPosY = -randPosY;

		// キューブの座標（Z軸）
		float randPosZ = random.GetRandomFloat(0, FIELD_POSITION_NORTH + -FIELD_POSITION_SOUTH);
		randPosZ += FIELD_POSITION_SOUTH;

		// キューブの座標（X軸）
		float randPosX = random.GetRandomFloat(0, FIELD_POSITION_EAST + -FIELD_POSITION_WEST);
		randPosX += FIELD_POSITION_WEST;

		VECTOR pos = VGet(randPosX, randPosY, randPosZ);
		VECTOR dir = VGet(0, 1, 0);
		float moveSpeed = random.GetRandomFloat(40, 70);
		float scale = random.GetRandomFloat(1.0f, 2.0f);

		// キューブの生成
		BackgroundCube* cube = new BackgroundCube(CollisionTag::BgCube, mt);
		cube->Create(pos, dir, moveSpeed, scale);
		cubes.push_back(cube);
	}
}

void BackgroundCubeManager::Update()
{
	for (auto cube : cubes)
	{
		// キューブの高さ
		float randPosY = random.GetRandomFloat(200, 300);
		randPosY = -randPosY;
		
		// キューブの座標（Z軸）
		float randPosZ = random.GetRandomFloat(0, FIELD_POSITION_NORTH + -FIELD_POSITION_SOUTH);
		randPosZ += FIELD_POSITION_SOUTH;

		VECTOR pos = VGet(FIELD_POSITION_EAST, randPosY, randPosZ);
		VECTOR dir = VGet(0, 1, 0);
		float moveSpeed = random.GetRandomFloat(40, 70);
		float scale = random.GetRandomFloat(1.0f, 2.0f);

		if (cube->IsExist())
		{
			cube->Update();
		}
		// 画面外に出た場合は新たに生成する
		else
		{
			cube->Initialize();
			cube->Create(pos, dir, moveSpeed, scale);
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
/// キューブの生成を行う
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
	float scale = random.GetRandomFloat(1.0f, 2.0f);

	for (auto cube : cubes)
	{
		// 画面外に出たキューブがないかチェック
		if (!cube->IsExist())
		{
			// 新たに生成
			cube->Initialize();
			cube->Create(pos, dir, moveSpeed, scale);
		}
	}
}
