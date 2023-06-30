#include "BehaviorTree.h"
#include "NodeBase.h"

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

bool BehaviorTree::IsUsedNode(NodeBase* inNode)
{
	for (auto itr = usedNode->begin(); itr != usedNode->end(); itr++)
	{
		if ((*itr)->GetName() == inNode->GetName())
		{
			return true;
		}
	}

	return false;
}

NodeBase* BehaviorTree::InferenceNode()
{
	// 使用済みノードのリセット
	usedNode->clear();
	NodeBase* node = nullptr;
	NodeBase* current = nullptr;

	int hierarchy = 1;

	// 何かしらの行動を決定するまで思考する
	while (node)
	{
		for (auto itr = aiTree->begin(); itr != aiTree->end(); itr++)
		{
			// 始端
			if ((*itr)->GetParent() == "")
			{
				current = (*itr);
				usedNode->push_back(*itr);
			}

			// 既に使用している場合はスキップ
			// 未使用の場合は現在のノードの子か確認
			if (current->GetName() == (*itr)->GetParent() &&
				!IsUsedNode(*itr))
			{
			}
			else
			{
				continue;
			}

		}
	}

	return node;
}

void BehaviorTree::ResetUsedNode()
{
	usedNode->clear();
}
