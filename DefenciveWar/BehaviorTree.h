#pragma once

#include <map>
#include <vector>
#include <string>

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
	class NodeBase* SelectNode(class NodeBase* inNode, std::vector<NodeBase*> inChild);
	bool SearchNode(std::string inName);
	bool IsUsedNode(NodeBase* inNode);
	NodeBase* InferenceNode();
	void ResetUsedNode();
private:

	class Random& random;

	NodeBase* curretNode;
	std::vector<NodeBase*> aiTree;			// �r�w�C�r�A�c���[
	std::vector<NodeBase*> usedNode;		// �g�p�ς݃m�[�h
};

