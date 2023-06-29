#include "BehaviorTree.h"

BehaviorTree::BehaviorTree()
{
}

BehaviorTree::~BehaviorTree()
{
}

void BehaviorTree::Initialize()
{
}

void BehaviorTree::EntryNode(NodeBase* inNode)
{
	aiTree->push_back(inNode);
}

bool BehaviorTree::SearchNode(std::string inName)
{
	for (auto itr = aiTree->begin(); itr != aiTree->end(); itr++)
	{
		if ((*itr)->GetName() == inName)
		{
			return true;
		}
	}

	return false;
}
