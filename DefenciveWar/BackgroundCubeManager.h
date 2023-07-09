#pragma once

#include <vector>
#include "BackgroundCube.h"
#include "ModelTypeData.h"

/// <summary>
/// ゲーム中背景に移るキューブの生成・更新・描画を行う
/// </summary>
class BackgroundCubeManager
{
public:
	BackgroundCubeManager(ModelType mt);
	~BackgroundCubeManager();

	void Initialize(ModelType mt);
	void Update();
	void Draw();
	void CreateCube();

private:
	const int CUBE_POOL_SIZE = 30;				// 画面に描画するキューブの総数

	class Random& random;

	std::vector<BackgroundCube*> cubes;			// キューブたち
};

