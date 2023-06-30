#pragma once

#include <string>
#include "BehaviorTree.h"

/// <summary>
/// �r�w�C�r�A�m�[�h���N���X
/// </summary>
class NodeBase
{
public:
	NodeBase(std::string inName, 
			 std::string inParent, 
			 int inHierarchy,
			 int inPriority,
			 BehaviorTree::SelectRule inRule,
			 class ActBase* inAction);
	~NodeBase();

	//virtual void Initialize() = 0;
	void Update();
	bool IsExecutabel();

	const std::string GetName() { return name; }
	const std::string GetParent() { return parent; }
	const BehaviorTree::SelectRule GetRule() { return rule; }
	const int GetHierarchy() { return hierarchy; }
	const int GetPriority() { return priority; }
	const ActBase* GetAction() { return action; }

protected:
	std::string name;						// ���O
	//NodeBase* parent;						// �e�̃m�[�h
	std::string parent;						// �e�̃m�[�h��
	BehaviorTree::SelectRule rule;			// �q�̑I����@
	int hierarchy;							// �ǂ̊K�w�ɏ������Ă��邩
	int priority;							// �D��x
	class ActBase* action;					// �s�����s

	std::vector<NodeBase*>* child;			// �m�[�h�̎q�����[

private:

};

