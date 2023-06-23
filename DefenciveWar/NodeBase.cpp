#include "common.h"
#include "ExecJudgmentBase.h"
#include "NodeBase.h"
#include "BossEnemy.h"
#include "BehaviorData.h"
#include "ActionBase.h"

//

NodeBase::NodeBase(std::string inName,
				   NodeBase* inParent,
				   NodeBase* inSibling,
				   int inPriority,
				   BehaviorTree::SelectRule inSelectRule,
				   ExecJudgmentBase* inJudgment,
				   ActionBase* inAction,
				   int inHierarchyNo)
	:name(inName),
	parent(inParent),
	sibling(inSibling),
	priority(inPriority),
	selectRule(inSelectRule),
	execJudgment(inJudgment),
	action(inAction),
	hierarchyNo(inHierarchyNo),
	child(NULL)

{
	// �����Ȃ�
}

NodeBase::~NodeBase()
{
	// �����Ȃ�
}

NodeBase* NodeBase::GetChild(int idx)
{
	if (child.size() >= idx)
	{
		return NULL;
	}

	return child[idx];
}

NodeBase* NodeBase::GetLastChild()
{
	if (child.size() == 0)
	{
		return NULL;
	}

	return child[child.size() - 1];
}

NodeBase* NodeBase::GetTopChild()
{
	if (child.size() == 0)
	{
		return NULL;
	}

	return child[0];
}

bool NodeBase::Judgment(BossEnemy* boss)
{
	if (execJudgment != NULL)
	{
		return execJudgment->Judgment(boss);
	}

	return true;
}

/// <summary>
/// �D�揇�ʑI��
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
NodeBase* NodeBase::SelectPriority(std::vector<NodeBase*>* list)
{
	NodeBase* select_node = NULL;
	int priority = -10000;

	// ��ԗD�揇�ʂ������m�[�h��T��
	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
		if (priority < (*itr)->GetPriority())
		{
			select_node = (*itr);
			priority = (*itr)->GetPriority();
		}
	}

	return select_node;
}

/// <summary>
/// �����_���I��
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
NodeBase* NodeBase::SelectRandom(std::vector<NodeBase*>* list)
{
	int selectNo = rand() % list->size();

	return (*list)[selectNo];
}

/// <summary>
/// �I���E�I�t�I��
/// </summary>
/// <param name="list"></param>
/// <param name="data"></param>
/// <returns></returns>
NodeBase* NodeBase::SelectOnOff(std::vector<NodeBase*>* list, BehaviorData* data)
{
	std::vector<NodeBase*> offList;

	// �g�p�ς݃m�[�h���X�g�A�b�v����
	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
		if (!data->IsNodeUsed((*itr)->GetName()))
		{
			offList.push_back(*itr);
		}
	}

	// ���X�g�A�b�v���������`�F�b�N
	if (offList.size() == 0)
	{
		// �m�[�h��S�ă��Z�b�g
		data->ResetNodeUsed(&child);
		offList = *list;
	}

	// �g�p�����m�[�h��o�^
	data->EntryUsedNode(offList[0]->GetName());

	// ���X�g�̐擪������m�[�h
	return offList[0];
}

/// <summary>
/// �V�[�P���X�I��
/// </summary>
/// <param name="list"></param>
/// <param name="data"></param>
/// <returns></returns>
NodeBase* NodeBase::SelectSequence(std::vector<NodeBase*>* list, BehaviorData* data)
{
	// ���̃m�[�h�̃V�[�P���X�̃X�e�b�v���擾
	int step = data->GetSequenceStep(GetName());

	// �V�[�P���X���I����Ă���I��
	if (step >= child.size())
	{
		if (selectRule != BehaviorTree::SelectRule::SequentialLooping)
		{
			return NULL;
		}
		else {
			// Looping�̏ꍇ�͓�������s
			step = 0;
		}
	}

	// ���Ԃ̃m�[�h�����s�ł��邩�̃`�F�b�N
	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
		if (child[step]->GetName() == (*itr)->GetName())
		{
			// �V�[�P���X�m�[�h���L�^
			data->PushSequenceNode(this);
			// �V�[�P���X�X�e�b�v���X�V
			data->SetSequenceStep(GetName(), step + 1);
			return child[step];
		}
	}

	return NULL;
}

/// <summary>
/// �m�[�h����
/// </summary>
/// <param name="searchName"></param>
/// <returns></returns>
NodeBase* NodeBase::SearchNode(std::string searchName)
{
	// ���O����v
	if (name == searchName)
	{
		return this;
	}
	else
	{
		// �q�m�[�h�Ō���
		for (auto itr = child.begin(); itr != child.end(); itr++)
		{
			NodeBase* ret = (*itr)->SearchNode(searchName);

			if (ret != NULL)
			{
				return ret;
			}
		}
	}

	return NULL;
}

/// <summary>
/// �m�[�h���_
/// </summary>
/// <param name="boss"></param>
/// <param name="data"></param>
/// <returns></returns>
NodeBase* NodeBase::Inference(BossEnemy* boss, BehaviorData* data)
{
	std::vector<NodeBase*> list;
	NodeBase* result = NULL;

	// �q�m�[�h�Ŏ��s�\�ȃm�[�h��T��
	for (int i = 0; i < child.size(); i++)
	{
		// ���s���肪����ꍇ
		if (child[i]->execJudgment != NULL)
		{
			// ���s���菈��
			if (child[i]->execJudgment->Judgment(boss))
			{
				list.push_back(child[i]);
			}
		}
		else
		{
			// ���菈�����Ȃ���Ζ������ɒǉ�
			list.push_back(child[i]);
		}
	}

	// �I�����[���Ńm�[�h�����肷��
	switch (selectRule)
	{
	case BehaviorTree::SelectRule::Priority:
		result = SelectPriority(&list);
		break;
	case BehaviorTree::SelectRule::Sequence:
	case BehaviorTree::SelectRule::SequentialLooping:
		result = SelectSequence(&list, data);
		break;
	case BehaviorTree::SelectRule::Random:
		result = SelectRandom(&list);
		break;
	case BehaviorTree::SelectRule::OnOff:
		result = SelectOnOff(&list, data);
		break;
	}

	if (result != NULL)
	{
		// �s��������ΏI��
		if (result->HasAction())
		{
			return result;
		}
		else
		{
			// ���܂����m�[�h�Ő��_�J�n
			result = result->Inference(boss, data);
		}
	}

	return result;
}

void NodeBase::PrintName()
{
	for (auto itr = child.begin(); itr != child.end(); itr++)
	{
		(*itr)->PrintName();
	}
}

ActionBase::State NodeBase::Run(BossEnemy* boss)
{
	if (action != NULL)
	{
		return action->Run(boss);
	}

	return ActionBase::FAILED;
}
