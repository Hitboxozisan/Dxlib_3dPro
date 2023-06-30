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

void BehaviorManager::Update()
{

}

void BehaviorManager::EntryNode(NodeBase* inNode)
{
	// ノードが既に登録されていないか
	if (aiTree->SearchNode(inNode->GetName()))
	{
		printfDx("ノードは既に登録されています_%S", inNode->GetName());
		return;
	}

	// ノードを登録
	aiTree->EntryNode(inNode);
}

NodeBase* BehaviorManager::InferenceNode()
{
	


	return nullptr;
}
