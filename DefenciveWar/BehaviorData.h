#pragma once

#include <vector>
#include <stack>
#include <map>

#include "BehaviorTree.h"

class BehaviorData
{
public:
	BehaviorData();
	~BehaviorData();

	void Initialize();
	void ResetNodeUsed(std::vector<NodeBase*>* reset_hierachy);				// �g�p�ς݃m�[�h�̃��Z�b�g
	void EntryUsedNode(std::string name) { usedNodeMap[name] = true; };		// �g�p�ς݃m�[�h�ɓo�^					// �g�p�ς݃m�[�h�ɓo�^

	class NodeBase* PopSequneceNode();
	void PushSequenceNode(NodeBase* node) { sequenceStack.push(node); };
	int GetSequenceStep(std::string name);			// �V�[�P���X�X�e�b�v�̃Q�b�^�[
	bool IsNodeUsed(std::string name);

	void SetSequenceStep(std::string name, int step) { runSequnceStepMap[name] = step; };

private:
	std::stack<class NodeBase*> sequenceStack;		// �V�[�P���X�m�[�h�X�^�b�N
	std::map<std::string, int> runSequnceStepMap;	// ���s�V�[�P���X�̃X�e�b�v�}�b�v
	std::map<std::string, bool> usedNodeMap;		// �g�p�ς݃m�[�h�}�b�v
};

