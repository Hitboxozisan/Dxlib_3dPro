#pragma once

#include <string>
#include "BehaviorTree.h"
#include "NodeBase.h"

/// <summary>
/// �m�[�h�̑I���E���s���s��
/// </summary>
class BehaviorManager final
{
public:
	BehaviorManager();
	~BehaviorManager();

	void Initialize();
	NodeBase* Update(NodeBase* inAction);
	
	void EntryNode(std::string inName, 
				   std::string inParent, 
				   int inHierarchy,
				   int inPriority, 
				   BehaviorTree::SelectRule inRule, 
				   class ActBase* inAction);
	NodeBase* InferenceNode();

private:
	class BehaviorTree* aiTree;
};
