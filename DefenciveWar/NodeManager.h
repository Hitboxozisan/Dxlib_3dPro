#pragma once

#include <vector>

// �I�����[��
enum class SelectionRule
{
	NONE,			// �Ȃ��i���[�m�[�h�j
	Priority,		// �D�揇
	Sequence,		// �V�[�N�G���X
	Random,			// �����_��
};

/// <summary>
/// �m�[�h�̐i�s�E�Ǘ����s��
/// �V���O���g���ł͂Ȃ��e����������
/// </summary>
class NodeManager
{
public:
	NodeManager();
	~NodeManager();

	void Initialize();
	void Update();

	void EntryNode(class NodeBase*);
	void EntryUsedNode(NodeBase*);;
	bool SearchUsedNode(NodeBase*);
	NodeBase* DecisionRunNode();
private:

	void RunNode(NodeBase*);

	NodeBase* parent;							// �e�̃m�[�h
	std::vector<NodeBase*>* tree;				// �m�[�h�S��
	std::vector<NodeBase*>* currentNode;		// ���݂̊K�w�m�[�h
	//std::vector<NodeBase*> child;
	std::vector<NodeBase*>* usedNode;
};

