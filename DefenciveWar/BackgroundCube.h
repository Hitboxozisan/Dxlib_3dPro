#pragma once

#include "Mover.h"

/// <summary>
/// ゲーム中背景のキューブ本体
/// </summary>
class BackgroundCube final : public Mover
{
public:
	BackgroundCube(CollisionTag tag);
	~BackgroundCube();

	void Create();
	void Update();
	void Draw();
private:

};

