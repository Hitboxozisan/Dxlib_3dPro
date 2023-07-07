#pragma once

#include <vector>
#include "BackgroundCube.h"

/// <summary>
/// ゲーム中背景に移るキューブの生成・更新・描画を行う
/// </summary>
class BackgroundCubeManager
{
public:
	BackgroundCubeManager();
	~BackgroundCubeManager();

	void Create();
	void Update();
	void Draw();

private:
	std::vector<BackgroundCube*> cubes;			// キューブたち
};

