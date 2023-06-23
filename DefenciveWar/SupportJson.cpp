#include "SupportJson.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>

SupportJson::SupportJson()
{
	filePath =
	{
		{JsonDataType::Player, "Data/Param/PlayerData.json"},
		{JsonDataType::BossEnemy, "Data/Param/BossEnemyData.json"},
	};

	// �t�@�C���̃��[�h
	Load();
}

SupportJson::~SupportJson()
{
}

/// <summary>
/// Json�t�@�C���̓ǂݍ���
/// </summary>
void SupportJson::Load()
{
	int size = static_cast<int>(JsonDataType::JsonDataAmount);
	for (int i = 0; i < size; i++)
	{
		JsonDataType jdt = static_cast<JsonDataType>(i);

		// �d���̓ǂݍ��݂�h�~
		for (int j = 0; j < size; j++)
		{
			JsonDataType jdt2 = static_cast<JsonDataType>(j);

			//if (i != j && filePath[jdt] == filePath[jdt2])
			//{
			//	printfDx("jsonFile[%d]_LoadError", j);
			//}

		}

		// �ǂ݂���
		std::ifstream ifs(filePath[jdt]);
		rapidjson::IStreamWrapper isw(ifs);
		doc[jdt].ParseStream(isw);
	}
	
}

void SupportJson::Entry(JsonDataType type, const char* datakey, float index)
{
}

int SupportJson::GetInt(JsonDataType type, const char* dataKey, const char* indexString, int index)
{
	int ret;
	if (index == -1)
	{
		ret = doc[type][dataKey].GetInt();
	}
	else
	{
		ret = doc[type][indexString][index][dataKey].GetInt();
	}

	return ret;
}

float SupportJson::GetFloat(JsonDataType type, const char* dataKey, const char* indexString, int index)
{
	float ret;
	if (index == -1)
	{
		ret = doc[type][dataKey].GetFloat();
	}

	return ret;
}

VECTOR SupportJson::GetVector(JsonDataType type, const char* dataKey, const char* indexString, int index)
{
	VECTOR ret;
	if (index == -1)
	{
		ret.x = doc[type][dataKey]["x"].GetFloat();
		ret.y = doc[type][dataKey]["y"].GetFloat();
		ret.z = doc[type][dataKey]["z"].GetFloat();
	}

	return ret;
}
