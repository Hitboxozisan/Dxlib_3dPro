#include "NodeBase.h"
#include "ActBase.h"


NodeBase::NodeBase(std::string inName, 
				   int inHierarchy, 
				   int inPriority, 
				   BehaviorTree::SelectRule inRule,
				   ActBase* inAction)
	:name(inName)
	,priority(inPriority)
	,rule(inRule)
	,action(inAction)
{
	child.clear();
}

NodeBase::~NodeBase()
{

}

ActBase::State NodeBase::Update()
{

	return ActBase::State::Run;
}

/// <summary>
/// 実行可能か
/// </summary>
/// <returns></returns>
bool NodeBase::IsExecutabel()
{
	// 実行アクションが存在しない場合は選択可能とする
	if (action == NULL)
	{
		return true;
	}

	// 実行可能か
	if (action->IsExecutabel())
	{
		return true;
	}

	return false;
}
