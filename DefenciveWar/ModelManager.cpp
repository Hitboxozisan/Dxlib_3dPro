#include "common.h"
#include "ModelManager.h"
#include "ModelData.h"

using namespace ModelData;

/// <summary>
/// コンストラクタ
/// </summary>
ModelManager::ModelManager()
{
	LoadAllModel();
}

/// <summary>
/// デストラクタ
/// </summary>
ModelManager::~ModelManager()
{
	DeleteAllModel();
}

/// <summary>
/// 指定したモデルの取得
/// </summary>
/// <param name="ModelType"></param>
/// <returns></returns>
const int& ModelManager::GetModelHandle(ModelType mt) const
{
	int index = static_cast<int>(mt);
	return modelHandle[index];
}

/// <summary>
/// 全てのモデルの読み込み
/// </summary>
void ModelManager::LoadAllModel()
{
	int size = static_cast<int>(ModelType::ModelAmount);
	// 各モデルの読み込み
	for (int i = 0; i < size; i++)
	{
		ModelType mt = static_cast<ModelType>(i);
		modelHandle[i] = MV1LoadModel(FILE_PATH[mt].c_str());
		// エラー処理
		if (modelHandle[i] < 0)
		{
			printfDx("Error_Model[%d]\n", i);
		}
	}
}

/// <summary>
/// 全てのモデルの削除
/// </summary>
void ModelManager::DeleteAllModel()
{
	int size = static_cast<int>(ModelType::ModelAmount);
	for (int i = 0; i < size; i++)
	{
		if (modelHandle[i] != NULL)
		{
			MV1DeleteModel(modelHandle[i]);
			modelHandle[i] = NULL;
		}
	}
}
