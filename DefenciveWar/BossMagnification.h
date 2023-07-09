#pragma once

#include <string>
#include <unordered_map>

/// <summary>
/// �v���C���[�ɍU����h���ꂽ�ۂ�
/// Trunkpoint�����ʂ�Ԃ�
/// </summary>
class BossMagnification final
{
public:
	BossMagnification();
	~BossMagnification();

	float GetMagnification(std::string attackName);

private:
	class SupportJson& json;
};

