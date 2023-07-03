#pragma once

#include <string>
#include <unordered_map>

/// <summary>
/// �v���C���[�ɍU�����K�[�h���ꂽ�ۂ�
/// Trunkpoint�����ʂ�Ԃ�
/// </summary>
class BossMagnification final
{
public:
	BossMagnification();
	~BossMagnification();

	//void EntryMagnification(std::string attackName);
	float GetMagnification(std::string attackName);

private:
	class SupportJson& json;

	//std::unordered_map<std::string, float> magnification;
};

