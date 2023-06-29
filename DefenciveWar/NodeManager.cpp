#include "EffekseerForDXLib.h"
#include "NodeManager.h"
#include "NodeBase.h"

NodeManager::NodeManager()
{
}

NodeManager::~NodeManager()
{
}

void NodeManager::Update()
{
	// Œ»Ý‚ÌŠK‘w
	// Žn’[‚Í 0
	int hierarchy = 0;
	std::string parent = "";

	for (auto itr = tree->begin(); itr != tree->end(); itr++)
	{
		// ƒm[ƒhŽn’[‚¾‚Á‚½ê‡
		if ((*itr)->GetParent() == "")
		{
			EntryUsedNode(*itr);
			hierarchy = 1;
			parent = (*itr)->GetName();
		}

		// Œ»Ý‚Ìƒm[ƒh‚ðÝ’è
		if ((*itr)->GetHierarchy() == hierarchy &&
			(*itr)->GetParent() == parent)
		{
			currentNode->push_back(*itr);
		}
	}

	RunNode(DecisionRunNode());
}

void NodeManager::EntryNode(NodeBase* node)
{
	tree->push_back(node);
}


void NodeManager::EntryUsedNode(NodeBase* node)
{
	usedNode->push_back(node);
}


bool NodeManager::SearchUsedNode(NodeBase* node)
{
	for (auto itr = usedNode->begin(); itr != usedNode->end() ; itr++)
	{
		if ((*itr)->GetName() == node->GetName())
		{
			return true;
		}
	}

	return false;
}

NodeBase* NodeManager::DecisionRunNode()
{
	for (auto itr = currentNode->begin(); itr != currentNode->end() ; itr++)
	{
		int priority = (*itr)->GetPriority();
		switch (parent->GetRule())
		{
		case SelectionRule::Priority:
			
			break;
		case SelectionRule::Sequence:
			if (!SearchUsedNode(*itr))
			{
				return *itr;
			}
			break;
		case SelectionRule::Random:

			break;
		}
	}

	return nullptr;
}


void NodeManager::RunNode(NodeBase* node)
{
	node->Update();
}
