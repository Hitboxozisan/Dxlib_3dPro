#pragma once

#include "NodeBase.h"

/// <summary>
/// ���s�m�[�h
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

