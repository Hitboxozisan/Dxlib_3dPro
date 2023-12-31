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
		// シークエンスの途中なのか
		inAction = aiTree->SequenceEnRoute();
		
		// 途中ならそこから再開する
		if (inAction != NULL)
		{
			inAction = aiTree->SelectNode(inAction);
		}
		else
		{
			return NULL;
		}
	}
	else if(state == ActBase::State::Failed)
	{
		// 続けるのかを判断
		if (inAction->GetAction()->IsContinue())
		{

		}
		// 続けない場合は終了する
		else
		{
			return NULL;
		}
	}
	
	return inAction;
}

void BehaviorManager::EntryNode(std::string inName, std::string inParent, int inHierarchy, int inPriority, BehaviorTree::SelectRule inRule, ActBase* inAction)
{
	// ノードが既に登録されていないか
	if (aiTree->SearchNode(inName))
	{
		printfDx("ノードは既に登録されています_%S", inName);
		return;
	}

	// ノードを登録
	aiTree->EntryNode(inName, inParent, inHierarchy, inPriority, inRule, inAction);
}

NodeBase* BehaviorManager::InferenceNode()
{
	NodeBase* node = aiTree->InferenceNode();
	return node;
}
