#include "DxLib.h"
#include "BehaviorManager.h"
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

void BehaviorManager::Update()
{
}

void BehaviorManager::EntryNode(NodeBase* inNode)
{
	// �m�[�h�����ɓo�^����Ă��Ȃ���
	if (aiTree->SearchNode(inNode->GetName()))
	{
		printfDx("�m�[�h�͊��ɓo�^����Ă��܂�_%S", inNode->GetName());
		return;
	}

	// �m�[�h��o�^
	aiTree->EntryNode(inNode);
}
