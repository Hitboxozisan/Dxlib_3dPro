#include "BehaviorTree.h"
#include "NodeBase.h"
#include "ActBase.h"
#include "Singleton.h"
#include "Random.h"
#include "DxLib.h"

BehaviorTree::BehaviorTree()
	:random(Singleton<Random>::GetInstance())
{
	Initialize();
}

BehaviorTree::~BehaviorTree()
{
}

void BehaviorTree::Initialize()
{
	// �c���[�̏�����
	aiTree.empty();
}

void BehaviorTree::EntryNode(std::string inName, std::string inParent, int inHierarchy, int inPriority, BehaviorTree::SelectRule inRule, ActBase* inAction)
{
	NodeBase* node = new NodeBase(inName, inHierarchy, inPriority, inRule, inAction);
	
	// �n�[�m�[�h�̏ꍇ
	if (aiTree.empty())
	{
		aiTree.push_back(node);
		return;
	}
	
	// �N���e���m�F
	// �e�̎q�m�[�h�ɒǉ�����
	for (auto itr = aiTree.begin(); itr != aiTree.end(); itr++)
	{
		if ((*itr)->GetName() == inParent)
		{
			// �q�̃m�[�h�Ƃ��Ēǉ�
			(*itr)->EntryChild(node);

			// �I����@���V�[�N�G���X�̏ꍇ��
			//if ((*itr)->GetRule() == SelectRule::Sequence)
			//{
			//	// �V�[�N�G���X�m�[�h�ɓo�^
			//	sequenceNode.push(node); 
			//}
		}
	}
	
	// �c���[�ɒǉ�
	aiTree.push_back(node);
}

NodeBase* BehaviorTree::SelectNode(NodeBase* inNode)
{
	activeNode.clear();
	std::vector<NodeBase*> inChild = inNode->GetChild();
	NodeBase* node = nullptr;

	// �q�̃m�[�h�̒�������s�\�ȃm�[�h��I��
	for (auto itr = inChild.begin(); itr != inChild.end(); itr++)
	{
		// �m�[�h�����s�\��
		if ((*itr)->IsExecutabel())
		{
			activeNode.push_back(*itr);
		}
	}

	// �q��	���s�\�m�[�h����I������
	switch (inNode->GetRule())
	{
	case SelectRule::None:
		node = *activeNode.begin();
		break;
	case SelectRule::Priority:
		node = SelectPriority();
		break;
	case SelectRule::Sequence:
		node = SelectSequence(inNode);
		break;
	case SelectRule::Random:
		node = SelectRandom();
		break;
	}

	// �m�[�h�����肵���ꍇ
	if (node != NULL)
	{
		// �s�����Ȃ��ꍇ�͎��̍s����I��
		if (node->GetAction() == NULL)
		{
			node = SelectNode(node);
		}
	}
	
	
	return node;
}

/// <summary>
/// �m�[�h�����݂��邩
/// </summary>
/// <param name="inName"></param>
/// <returns></returns>
bool BehaviorTree::SearchNode(std::string inName)
{
	if (aiTree.empty())
	{
		return false;
	}

	for (auto itr = aiTree.begin(); itr != aiTree.end(); itr++)
	{
		if ((*itr)->GetName() == inName)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �m�[�h���g�p�ς݂�
/// </summary>
/// <param name="inNode"></param>
/// <returns></returns>
bool BehaviorTree::IsUsedNode(NodeBase* inNode)
{
	for (auto itr = usedNode.begin(); itr != usedNode.end(); itr++)
	{
		if ((*itr)->GetName() == inNode->GetName())
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �V�[�N�G���X�̓r����
/// </summary>
/// <returns></returns>
NodeBase* BehaviorTree::SequenceEnRoute()
{
	NodeBase* node = NULL;

	// �V�[�N�G���X�̓r���Ȃ玟�̃V�[�N�G���X��Ԃ�
	if (!sequenceNode.empty())
	{
		if (sequenceNode.top()->GetAction() == NULL)
		{
			sequenceNode.pop();
		}
		else
		{
			node = sequenceNode.top();
		}
		
		// �g�p����m�[�h���V�[�N�G���X����폜����
		sequenceNode.pop();
		return node;
	}
	else
	{
		return NULL;
	}
}

/// <summary>
/// �m�[�h�𐄘_
/// </summary>
/// <returns></returns>
NodeBase* BehaviorTree::InferenceNode()
{
	// �g�p�ς݃m�[�h�̃��Z�b�g
	usedNode.clear();
	NodeBase* node = *aiTree.begin();

	// ���[�m�[�h�ɂȂ�܂ŌJ��Ԃ�
	while (!node->GetChildEmpty())
	{
		// �q�̒�����ǂ̃m�[�h��I�Ԃ��I��
		node = SelectNode(node);
	}

	return node;
}

/// <summary>
/// �g�p�ς݃m�[�h�̏�����
/// </summary>
void BehaviorTree::ResetUsedNode()
{
	usedNode.clear();
}

/// <summary>
/// Priority�I��
/// </summary>
/// <param name="inNode"></param>
/// <returns></returns>
NodeBase* BehaviorTree::SelectPriority()
{
	int priority = 100;
	NodeBase* node = NULL;

	for (auto itr = activeNode.begin(); itr != activeNode.end(); itr++)
	{
		if ((*itr)->GetPriority() <= priority &&
			!IsUsedNode((*itr)))
		{
			priority = (*itr)->GetPriority();
			node = (*itr);
		}
	}

	return node;
}

/// <summary>
/// Sequence�I��
/// </summary>
/// <param name="inNode"></param>
/// <returns></returns>
NodeBase* BehaviorTree::SelectSequence(NodeBase* inParent)
{
	for (auto itr = activeNode.begin(); itr != activeNode.end(); itr++)
	{
		sequenceNode.push(*itr);
	}
	NodeBase* result = sequenceNode.top();
	sequenceNode.pop();

	return result;
}

/// <summary>
/// Random�I��
/// �e�m�[�h�ψ�Ȋm��
/// </summary>
/// <param name="inNode"></param>
/// <returns></returns>
NodeBase* BehaviorTree::SelectRandom()
{
	int rand = random.GetRandomInt(0, activeNode.size());

	return activeNode[rand];
}
