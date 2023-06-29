#include "NodeBase.h"
#include "NodeAssault.h"
#include "BossEnemy.h"

NodeAssault::NodeAssault(std::string inName, std::string inParent, int inPriority, BossEnemy* inEnemy)
	:NodeBase(inName, inParent, inPriority)
	,enemy(inEnemy)
{
}

NodeAssault::~NodeAssault()
{
}

void NodeAssault::Update()
{
}

bool NodeAssault::IsExecutabel()
{
	return false;
}
