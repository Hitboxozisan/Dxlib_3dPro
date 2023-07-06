#pragma once

#include <map>
#include <vector>
#include <string>
#include <stack>

/// <summary>
/// �r�w�C�r�A�c���[�{��
/// </summary>
class BehaviorTree final
{
public:
	BehaviorTree();
	~BehaviorTree();

	// �I�����[��
	enum class SelectRule
	{
		None,			// �Ȃ��i���[�m�[�h�j
		Priority,		// �D�揇
		Sequence,		// �V�[�N�G���X
		Random,			// �����_��
	};

	void Initialize();
	void EntryNode(std::string inName, 
				   std::string inParent, 
				   int inHierarchy, 
				   int inPriority,
				   BehaviorTree::SelectRule inRule, 
				   class ActBase* inAction);
	class NodeBase* SelectNode(class NodeBase* inNode);
	bool SearchNode(std::string inName);
	bool IsUsedNode(NodeBase* inNode);
	NodeBase* SequenceEnRoute();
	NodeBase* InferenceNode();
	void ResetUsedNode();

	NodeBase* SelectPriority();
	NodeBase* SelectSequence(NodeBase* inParent);
	NodeBase* SelectRandom();
private:

	class Random& random;

	std::vector<NodeBase*> aiTree;			// �r�w�C�r�A�c���[
	std::vector<NodeBase*> activeNode;		// ���s�\�m�[�h
	std::vector<NodeBase*> usedNode;		// �g�p�ς݃m�[�h
	std::stack<NodeBase*> sequenceNode;		// �V�[�N�G���X�m�[�h
};

