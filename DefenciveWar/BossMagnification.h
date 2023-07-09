#pragma once

#include <string>
#include <unordered_map>

/// <summary>
/// vC[ΙUπhͺκ½ΫΜ
/// TrunkpointΑΚπΤ·
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

