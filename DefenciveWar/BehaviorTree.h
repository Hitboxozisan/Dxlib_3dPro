#pragma once

#include <map>
#include <vector>
#include "NodeBase.h"

/// <summary>
/// �r�w�C�r�A�c���[�{��
/// </summary>
class BehaviorTree final
{
public:
	BehaviorTree();
	~BehaviorTree();

	// �I�����[��
	enum class SelectionRule
	{
		NONE,			// �Ȃ��i���[�m�[�h�j
		Priority,		// �D�揇
		Sequence,		// �V�[�N�G���X
		Random,			// �����_��
	};

	void Initialize();
	void EntryNode(class NodeBase* inNode);
	bool SearchNode(std::string inName);
	void Reset();

private:
	std::vector<NodeBase*>* aiTree;
};

