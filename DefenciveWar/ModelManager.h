#pragma once

#include "ModelTypeData.h"

/// <summary>
/// ���f���Ǘ��N���X
/// ���f���̓ǂݍ��݁E�Ǘ����s��
/// �V���O���g��
/// </summary>
class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	const int& GetModelHandle(ModelType mt) const;

private:
	void LoadAllModel();
	void DeleteAllModel();

	int modelHandle[static_cast<int>(ModelType::ModelAmount)];

};

