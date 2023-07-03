#include "BehaviorTree.h"
#include "NodeBase.h"
#include "ActBase.h"
#include "Singleton.h"
#include "Random.h"

BehaviorTree::BehaviorTree()
	:random(Singleton<Random>::GetInstance())
{
	Initialize();
}

BehaviorTree::~BehaviorTree()
{
}

void BehaviorTree::Initialize()
{
	aiTree.empty();
}

void BehaviorTree::EntryNode(std::string inName, std::string inParent, int inHierarchy, int inPriority, BehaviorTree::SelectRule inRule, ActBase* inAction)
{
	NodeBase* node = new NodeBase(inName, inHierarchy, inPriority, inRule, inAction);
	
	if (aiTree.empty())
	{
		aiTree.push_back(node);
	}
	
	// 誰が親か確認
	// 親の子ノードに追加する
	for (auto itr = aiTree.begin(); itr != aiTree.end(); itr++)
	{
		if ((*itr)->GetName() == inParent)
		{
			(*itr)->EntryChild(node);
		}
	}
	
	// ツリーに追加
	aiTree.push_back(node);
}

NodeBase* BehaviorTree::SelectNode(NodeBase* inNode, std::vector<NodeBase*> inChild)
{
	int priority = 0;
	NodeBase* node = nullptr;
	
	// 子のノードから選択する
	for (auto itr = inChild.begin(); itr != inChild.end(); itr++)
	{
	
		switch (inNode->GetRule())
		{
		case SelectRule::None:
			node = *inChild.begin();
	
		case SelectRule::Priority:
			if (priority <= (*itr)->GetPriority())
			{
				priority = (*itr)->GetPriority();
				node = (*itr);
			}
		case SelectRule::Sequence:
			if (IsUsedNode(*itr))
			{
				node = (*itr);
			}
	
		case SelectRule::Random:
			if ((*itr)->IsExecutabel())
			{
				node = (*itr);
			}
	
		}
	
		if (node != nullptr) break;
	}
	
	return node;
}


bool BehaviorTree::SearchNode(std::string inName)
{
	if (aiTree.empty())
	{
		return false;
	}

	for (auto itr = aiTree.begin(); itr != aiTree.end(); itr++)
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
	for (auto itr = usedNode.begin(); itr != usedNode.end(); itr++)
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
	usedNode.clear();
	NodeBase* node = nullptr;

	int hierarchy = 1;

	// 何かしらの行動を決定するまで思考する
	
	for (auto itr = aiTree.begin(); itr != aiTree.end(); itr++)
	{
		// 使用済みノードはスキップ
		if (IsUsedNode(*itr))
		{
			continue;
		}
	
		// 子がいる場合は次のノードの選択
		if (!(*itr)->GetChildEmpty() &&
			(*itr)->GetHierarchy() == hierarchy)
		{
			hierarchy++;
			node = SelectNode(*itr, (*itr)->GetChild());
		}
		// いない場合はそのノードを選択
		else
		{
			node = (*itr);
		}
		
	}
	

	return node;
}

void BehaviorTree::ResetUsedNode()
{
	usedNode.clear();
}
