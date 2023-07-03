#pragma once

#include <string>
#include <unordered_map>

/// <summary>
/// vC[ΙUπK[h³κ½ΫΜ
/// TrunkpointΑΚπΤ·
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

