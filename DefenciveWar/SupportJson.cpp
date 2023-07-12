#include "SupportJson.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>

SupportJson::SupportJson()
{
	filePath =
	{
		{JsonDataType::Player, "Data/Param/PlayerData.json"},
		{JsonDataType::BossEnemy, "Data/Param/BossEnemyData.json"},
		{JsonDataType::BossMagnification, "Data/Param/BossMagnificationData.json"},
		{JsonDataType::Result, "Data/Param/Result.json"},
	};

	// ファイルのロード
	Load();
}

SupportJson::~SupportJson()
{
}

/// <summary>
/// Jsonファイルの読み込み
/// </summary>
void SupportJson::Load()
{
	int size = static_cast<int>(JsonDataType::JsonDataAmount);
	for (int i = 0; i < size; i++)
	{
		JsonDataType jdt = static_cast<JsonDataType>(i);

		// 重複の読み込みを防止
		for (int j = 0; j < size; j++)
		{
			JsonDataType jdt2 = static_cast<JsonDataType>(j);

			//if (i != j && filePath[jdt] == filePath[jdt2])
			//{
			//	printfDx("jsonFile[%d]_LoadError", j);
			//}

		}

		// 読みこみ
		std::ifstream ifs(filePath[jdt]);
		rapidjson::IStreamWrapper isw(ifs);
		doc[jdt].ParseStream(isw);
	}
	
}

void SupportJson::Entry(JsonDataType type, const char* datakey, float index)
{
}

void SupportJson::SetFloat(JsonDataType type, const char* dataKey, const char* indexString, int index, float insertValue)
{
	float ret = insertValue;
	if (index == -1)
	{
		doc[type][dataKey].SetFloat(ret);
	}
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
