#include "BehaviorData.h"
#include "NodeBase.h"

BehaviorData::BehaviorData()
{
	// �V�[�P���X���폜
	Initialize();
}

BehaviorData::~BehaviorData()
{
}

/// <summary>
/// ����������
/// </summary>
void BehaviorData::Initialize()
{
	// ���s�V�[�P���X�̃X�e�b�v�}�b�v�����Z�b�g
	runSequnceStepMap.clear();
	// �V�[�P���X�m�[�h�X�^�b�N���폜
	while (sequenceStack.size() > 0)
	{
		sequenceStack.pop();
	}
}

/// <summary>
/// �V�[�P���X�m�[�h�̃|�b�v
/// </summary>
/// <returns></returns>
NodeBase* BehaviorData::PopSequneceNode()
{
	// ��Ȃ�NULL
	if (sequenceStack.empty() != 0)
	{
		return NULL;
	}

	NodeBase* node = sequenceStack.top();

	if (node != NULL)
	{
		// ���o�����f�[�^���폜
		sequenceStack.pop();
	}

	return node;
}

/// <summary>
/// ���݂̃V�[�P���X�X�e�b�v�̎擾
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
int BehaviorData::GetSequenceStep(std::string name)
{
	return 0;
}

bool BehaviorData::IsNodeUsed(std::string name)
{
	// �g�p���ĂȂ�������false
	if (usedNodeMap.count(name) == 0)
	{
		return false;
	}

	return usedNodeMap[name];
}

/// <summary>
/// �g�p�m�[�h�̃��Z�b�g
/// </summary>
/// <param name="reset_hierachy"></param>
void BehaviorData::ResetNodeUsed(std::vector<NodeBase*>* reset_hierachy)
{
	for (auto itr = reset_hierachy->begin(); itr != reset_hierachy->end(); itr++)
	{
		usedNodeMap[(*itr)->GetName()] = false;
	}
}
