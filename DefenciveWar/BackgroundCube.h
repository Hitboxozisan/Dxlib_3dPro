#pragma once

#include "Mover.h"
#include "ModelTypeData.h"

/// <summary>
/// �Q�[�����w�i�̃L���[�u�{��
/// </summary>
class BackgroundCube final : public Mover
{
public:
	BackgroundCube(CollisionTag tag, ModelType mt);
	~BackgroundCube();

	void Initialize();
	void Create(VECTOR pos, VECTOR dir, float moveSpeed);
	void Update();
	void Draw();

private:
	class ModelManager& modelMgr;
	
	float speed;

	void Move();
	void OutOfWindow();
};

