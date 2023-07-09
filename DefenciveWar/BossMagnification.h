#pragma once

#include <string>
#include <unordered_map>

/// <summary>
/// ƒvƒŒƒCƒ„[‚ÉUŒ‚‚ğ–h‚ª‚ê‚½Û‚Ì
/// Trunkpoint‘‰Á—Ê‚ğ•Ô‚·
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

