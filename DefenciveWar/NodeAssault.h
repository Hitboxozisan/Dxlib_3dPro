#pragma once

#include "NodeBase.h"

/// <summary>
/// é¿çsÉmÅ[Éh
/// </summary>
class NodeAssault final : public NodeBase
{
public:
	NodeAssault(std::string inName, 
				std::string inParent, 
				int inPriority,
				class BossEnemy* inEnemy);
	~NodeAssault();

	void Update();
	bool IsExecutabel();

private:
	BossEnemy* enemy;
};

