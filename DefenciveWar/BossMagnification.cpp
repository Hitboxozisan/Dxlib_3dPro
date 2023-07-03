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
/// �v�f�̒ǉ�������
/// </summary>
/// <param name="attackName"></param>
//void BossMagnification::EntryMagnification(std::string attackName)
//{
//	const char* name = attackName.c_str();
//	float mag = json.GetFloat(JsonDataType::BossMagnification, name);
//
//	// �v�f�̒ǉ�
//	magnification.insert(std::make_pair(attackName, mag));
//}

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
