#include "DxLib.h"
#include "BehaviorManager.h"
#include "NodeBase.h"
#include "BehaviorTree.h"

BehaviorManager::BehaviorManager()
	:aiTree(new BehaviorTree())
{

}

BehaviorManager::~BehaviorManager()
{
}

void BehaviorManager::Initialize()
{
}

NodeBase* BehaviorManager::Update(NodeBase* inAction)
{
	ActBase::State state = inAction->GetAction()->Run();

	if (state == ActBase::State::Complete)
	{
		return nullptr;
	}
	else if(state == ActBase::State::Failed)
	{
		// ������̂��𔻒f
		if (inAction->GetAction()->IsContinue())
		{

		}
		// �����Ȃ��ꍇ�͏I������
		else
		{
			return nullptr;
		}
	}

	return inAction;
}

void BehaviorManager::EntryNode(std::string inName, std::string inParent, int inHierarchy, int inPriority, BehaviorTree::SelectRule inRule, ActBase* inAction)
{
	// �m�[�h�����ɓo�^����Ă��Ȃ���
	if (aiTree->SearchNode(inName))
	{
		printfDx("�m�[�h�͊��ɓo�^����Ă��܂�_%S", inName);
		return;
	}

	// �m�[�h��o�^
	aiTree->EntryNode(inName, inParent, inHierarchy, inPriority, inRule, inAction);
}

NodeBase* BehaviorManager::InferenceNode()
{
	NodeBase* node = aiTree->InferenceNode();
	return node;
}
