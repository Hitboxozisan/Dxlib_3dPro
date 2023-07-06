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
/// ���s�\��
/// </summary>
/// <returns></returns>
bool NodeBase::IsExecutabel()
{
	// ���s�A�N�V���������݂��Ȃ��ꍇ�͑I���\�Ƃ���
	if (action == NULL)
	{
		return true;
	}

	// ���s�\��
	if (action->IsExecutabel())
	{
		return true;
	}

	return false;
}
