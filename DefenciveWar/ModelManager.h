#pragma once

#include "ModelTypeData.h"

/// <summary>
/// モデル管理クラス
/// モデルの読み込み・管理を行う
/// シングルトン
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

