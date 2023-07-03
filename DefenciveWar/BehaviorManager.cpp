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
		// ‘±‚¯‚é‚Ì‚©‚ð”»’f
		if (inAction->GetAction()->IsContinue())
		{

		}
		// ‘±‚¯‚È‚¢ê‡‚ÍI—¹‚·‚é
		else
		{
			return nullptr;
		}
	}

	return inAction;
}

void BehaviorManager::EntryNode(std::string inName, std::string inParent, int inHierarchy, int inPriority, BehaviorTree::SelectRule inRule, ActBase* inAction)
{
	// ƒm[ƒh‚ªŠù‚É“o˜^‚³‚ê‚Ä‚¢‚È‚¢‚©
	if (aiTree->SearchNode(inName))
	{
		printfDx("ƒm[ƒh‚ÍŠù‚É“o˜^‚³‚ê‚Ä‚¢‚Ü‚·_%S", inName);
		return;
	}

	// ƒm[ƒh‚ð“o˜^
	aiTree->EntryNode(inName, inParent, inHierarchy, inPriority, inRule, inAction);
}

NodeBase* BehaviorManager::InferenceNode()
{
	NodeBase* node = aiTree->InferenceNode();
	return node;
}
