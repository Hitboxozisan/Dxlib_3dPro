#include "NodeBase.h"
#include "ActBase.h"


NodeBase::NodeBase(std::string inName, 
				   std::string inParent,
				   int inHierarchy, 
				   int inPriority, 
				   BehaviorTree::SelectRule inRule,
				   ActBase* inAction)
	:name(inName)
	,parent(inParent)
	,priority(inPriority)
	,rule(inRule)
	,action(inAction)
{

}

NodeBase::~NodeBase()
{

}

void NodeBase::Update()
{
}

bool NodeBase::IsExecutabel()
{
	return false;
}
