#include "common.h"
#include "ModelManager.h"
#include "ModelData.h"

using namespace ModelData;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ModelManager::ModelManager()
{
	LoadAllModel();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ModelManager::~ModelManager()
{
	DeleteAllModel();
}

/// <summary>
/// �w�肵�����f���̎擾
/// </summary>
/// <param name="ModelType"></param>
/// <returns></returns>
const int& ModelManager::GetModelHandle(ModelType mt) const
{
	int index = static_cast<int>(mt);
	return modelHandle[index];
}

/// <summary>
/// �S�Ẵ��f���̓ǂݍ���
/// </summary>
void ModelManager::LoadAllModel()
{
	int size = static_cast<int>(ModelType::ModelAmount);
	// �e���f���̓ǂݍ���
	for (int i = 0; i < size; i++)
	{
		ModelType mt = static_cast<ModelType>(i);
		modelHandle[i] = MV1LoadModel(FILE_PATH[mt].c_str());
		// �G���[����
		if (modelHandle[i] < 0)
		{
			printfDx("Error_Model[%d]\n", i);
		}
	}
}

/// <summary>
/// �S�Ẵ��f���̍폜
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
