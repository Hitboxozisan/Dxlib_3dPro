#pragma once

#include <string>
#include <unordered_map>

/// <summary>
/// プレイヤーに攻撃をガードされた際の
/// Trunkpoint増加量を返す
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

