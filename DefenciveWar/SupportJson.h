#pragma once

#include <unordered_map>
#include "JsonDataType.h"
#include "rapidjson/document.h"
#include "DxLib.h"

/// <summary>
/// Json�t�@�C���̓ǂݍ��݁E�f�[�^�̌Ăяo�����s��
/// �V���O���g��
/// </summary>
class SupportJson
{
public:
	SupportJson();
	~SupportJson();

	void Load();
	void Entry(JsonDataType type, const char* datakey, float index);

	int GetInt(JsonDataType type, const char* dataKey, const char* indexString = nullptr, int index = -1);
	float GetFloat(JsonDataType type, const char* dataKey, const char* indexString = nullptr, int index = -1);
	VECTOR GetVector(JsonDataType type, const char* dataKey, const char* indexString = nullptr, int index = -1);

private:
	std::unordered_map<JsonDataType, rapidjson::Document> doc;
	std::unordered_map<JsonDataType, const char*> filePath;
};

