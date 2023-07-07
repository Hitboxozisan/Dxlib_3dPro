#pragma once

#include <vector>
#include "BackgroundCube.h"

/// <summary>
/// �Q�[�����w�i�Ɉڂ�L���[�u�̐����E�X�V�E�`����s��
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
	std::vector<BackgroundCube*> cubes;			// �L���[�u����
};

