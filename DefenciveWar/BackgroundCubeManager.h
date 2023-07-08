#pragma once

#include <vector>
#include "BackgroundCube.h"
#include "ModelTypeData.h"

/// <summary>
/// �Q�[�����w�i�Ɉڂ�L���[�u�̐����E�X�V�E�`����s��
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
	const int CUBE_POOL_SIZE = 15;				// ��ʂɕ`�悷��L���[�u�̑���

	class Random& random;

	std::vector<BackgroundCube*> cubes;			// �L���[�u����
};

