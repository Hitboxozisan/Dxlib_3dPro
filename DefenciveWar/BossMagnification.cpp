#include "BossMagnification.h"
#include "Singleton.h"
#include "SupportJson.h"
#include "JsonDataType.h"

BossMagnification::BossMagnification()
	:json(Singleton<SupportJson>::GetInstance())
{
	// 念のためクリアしておく
	//magnification.clear();
}

BossMagnification::~BossMagnification()
{
}

/// <summary>
/// ボスのTrunkpoint増加量を返す
/// </summary>
/// <param name="attackName"></param>
/// <returns></returns>
float BossMagnification::GetMagnification(std::string attackName)
{
	const char* name = attackName.c_str();
	float mag = json.GetFloat(JsonDataType::BossMagnification, name);
	return mag;
}
