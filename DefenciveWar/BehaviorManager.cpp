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
	// ƒm[ƒh‚ªŠù‚É“o˜^‚³‚ê‚Ä‚¢‚È‚¢‚©
	if (aiTree->SearchNode(inNode->GetName()))
	{
		printfDx("ƒm[ƒh‚ÍŠù‚É“o˜^‚³‚ê‚Ä‚¢‚Ü‚·_%S", inNode->GetName());
		return;
	}

	// ƒm[ƒh‚ð“o˜^
	aiTree->EntryNode(inNode);
}

NodeBase* BehaviorManager::InferenceNode()
{
	


	return nullptr;
}
