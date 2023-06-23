#pragma once

#include <string>

class BehaviorTree
{
public:
	// �I�����[��
	enum class SelectRule
	{
		None,
		Priority,			// �D�揇��
		Sequence,			// �V�[�P���X
		SequentialLooping,	// �V�[�P���V�������[�s���O
		Random,				// �����_��
		OnOff,				// �I���E�I�t
	};

	void Initialize();
	class NodeBase* Inference(class BossEnemy* boss, class BehaviorData* data);

	// �V�[�P���X�m�[�h���琄�_
	NodeBase* SequenceBack(NodeBase* sequenceNode, BossEnemy* boss, BehaviorData* data);

	// �m�[�h�ǉ�
	void AddNode(std::string searchName, std::string entryName, int priority, SelectRule rule, class ExecJudgmentBase* judgment, class ActionBase* action);

	// ���s����
	NodeBase* Run(BossEnemy* boss, NodeBase* action, BehaviorData* data);
private:
	NodeBase* root;			// ���[�g�m�[�h
};

