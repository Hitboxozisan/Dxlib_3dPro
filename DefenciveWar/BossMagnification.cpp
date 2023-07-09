#include "BossMagnification.h"
#include "Singleton.h"
#include "SupportJson.h"
#include "JsonDataType.h"

BossMagnification::BossMagnification()
	:json(Singleton<SupportJson>::GetInstance())
{
	// �O�̂��߃N���A���Ă���
	//magnification.clear();
}

BossMagnification::~BossMagnification()
{
}

/// <summary>
/// �{�X��Trunkpoint�����ʂ�Ԃ�
/// </summary>
/// <param name="attackName"></param>
/// <returns></returns>
float BossMagnification::GetMagnification(std::string attackName)
{
	const char* name = attackName.c_str();
	float mag = json.GetFloat(JsonDataType::BossMagnification, name);
	return mag;
}
