#pragma once

#include <string>
#include <stack>
#include "BehaviorTree.h"
#include "ActBase.h"

/// <summary>
/// �r�w�C�r�A�m�[�h���N���X
/// </summary>
class NodeBase
{
public:
	NodeBase(std::string inName, 
			 int inHierarchy,
			 int inPriority,
			 BehaviorTree::SelectRule inRule,
			 class ActBase* inAction);
	~NodeBase();

	//virtual void Initialize() = 0;
	ActBase::State Update();
	bool IsExecutabel();
	void EntryChild(NodeBase* inNode) { child.push_back(inNode); }
	void EntrySequence(NodeBase* inNode) { sequenceNode.push(inNode); }

	const std::string GetName() { return name; }
	//const std::string GetParent() { return parent; }
	const BehaviorTree::SelectRule GetRule() { return rule; }
	const int GetHierarchy() { return hierarchy; }
	const int GetPriority() { return priority; }
	ActBase* GetAction() { return action; }
	const bool GetChildEmpty() { return child.empty(); }
	std::vector<NodeBase*> GetChild() { return child; }
	std::stack<NodeBase*> GetSequence() { return sequenceNode; }

	class ActBase* action;					// ���s�A�N�V����
protected:
	std::string name;						// ���O
	//NodeBase* parent;						// �e�̃m�[�h
	NodeBase* parent;						// �e�̃m�[�h
	BehaviorTree::SelectRule rule;			// �q�̑I����@
	int hierarchy;							// �ǂ̊K�w�ɏ������Ă��邩
	int priority;							// �D��x

	std::vector<NodeBase*> child;			// �m�[�h�̎q�����[
	std::stack<NodeBase*> sequenceNode;		// �V�[�N�G���X�m�[�h

private:

};

