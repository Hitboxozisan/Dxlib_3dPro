#pragma once

#include "Mover.h"

/// <summary>
/// �Q�[�����w�i�̃L���[�u�{��
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

