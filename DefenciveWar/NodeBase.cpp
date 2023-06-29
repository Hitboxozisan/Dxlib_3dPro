#include "NodeBase.h"

NodeBase::NodeBase(std::string inName, std::string inParent, int inPriority)
	:name(inName)
	,parent(inParent)
	,priority(inPriority)
{

}

NodeBase::~NodeBase()
{

}
