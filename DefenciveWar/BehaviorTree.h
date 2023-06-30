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
	enum SelectRule
	{
		None,			// �Ȃ��i���[�m�[�h�j
		Priority,		// �D�揇
		Sequence,		// �V�[�N�G���X
		Selector,		// �Z���N�^�[
		Random,			// �����_��
	};

	void Initialize();
	void EntryNode(class NodeBase* inNode);
	bool SearchNode(std::string inName);
	bool IsUsedNode(NodeBase* inNode);
	NodeBase* InferenceNode();
	void ResetUsedNode();
private:
	std::vector<NodeBase*>* aiTree;			// �r�w�C�r�A�c���[
	std::vector<NodeBase*>* usedNode;		// �g�p�ς݃m�[�h
};

