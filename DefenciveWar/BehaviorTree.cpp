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
	// �g�p�ς݃m�[�h�̃��Z�b�g
	usedNode->clear();
	NodeBase* node = nullptr;
	NodeBase* current = nullptr;

	int hierarchy = 1;

	// ��������̍s�������肷��܂Ŏv�l����
	while (node)
	{
		for (auto itr = aiTree->begin(); itr != aiTree->end(); itr++)
		{
			// �n�[
			if ((*itr)->GetParent() == "")
			{
				current = (*itr);
				usedNode->push_back(*itr);
			}

			// ���Ɏg�p���Ă���ꍇ�̓X�L�b�v
			// ���g�p�̏ꍇ�͌��݂̃m�[�h�̎q���m�F
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
