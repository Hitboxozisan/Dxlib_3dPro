#include "common.h"
#include "BehaviorTree.h"
#include "BehaviorData.h"
#include "NodeBase.h"

void BehaviorTree::Initialize()
{

}


NodeBase* BehaviorTree::Inference(BossEnemy* boss, BehaviorData* data)
{
    // �f�[�^�����Z�b�g���Ă���J�n
    data->Initialize();
    return root->Inference(boss, data);
}

/// <summary>
/// �V�[�P���X�m�[�h���琄�_
/// </summary>
/// <param name="sequenceNode"></param>
/// <param name="boss"></param>
/// <param name="data"></param>
/// <returns></returns>
NodeBase* BehaviorTree::SequenceBack(NodeBase* sequenceNode, BossEnemy* boss, BehaviorData* data)
{
    return sequenceNode->Inference(boss, data);
}

/// <summary>
/// �m�[�h�̒ǉ�
/// </summary>
/// <param name="search_name"></param>
/// <param name="entry_name"></param>
/// <param name="priority"></param>
/// <param name="select_rule"></param>
/// <param name="judgment"></param>
/// <param name="action"></param>
void BehaviorTree::AddNode(std::string searchName, std::string entryName, int priority, SelectRule rule, ExecJudgmentBase* judgment, ActionBase* action)
{
    // �����m�[�h������ꍇ
    if (searchName != "")
    {
        // �m�[�h����������
        NodeBase* searchNode = root->SearchNode(searchName);

        // �m�[�h�����������ꍇ
        if (searchNode != NULL)
        {
            // �m�[�h�̖������擾
            NodeBase* sibling = searchNode->GetLastChild();
            // �V�K�m�[�h���쐬
            NodeBase* addNode = new NodeBase(entryName, searchNode, sibling, priority, rule, judgment, action, 1);

            searchNode->AddChaild(addNode);
        }

    }
    // �Ȃ��ꍇ
    else
    {
        // ���[�g�m�[�h���Ȃ��ꍇ�͐V�K���[�g�m�[�h��
        if (root == NULL)
        {
            root = new NodeBase(entryName, NULL, NULL, priority, rule, judgment, action, 1);
        }
        else
        {
            printfDx("���[�g�͊��ɓo�^����Ă��܂�\n");
        }
    }
}

/// <summary>
/// �m�[�h�̎��s
/// </summary>
/// <param name="boss"></param>
/// <param name="action"></param>
/// <param name="data"></param>
/// <returns></returns>
NodeBase* BehaviorTree::Run(BossEnemy* boss, NodeBase* action, BehaviorData* data)
{
    // �m�[�h�̎��s
    ActionBase::State state = action->Run(boss);

    // ����ɏI�������ꍇ
    if (state == ActionBase::State::COMPLETE)
    {
        // �V�[�P���X�̓r�����𔻒f
        NodeBase* sequenceNode = data->PopSequneceNode();

        // �r������Ȃ��Ȃ�I��
        if (sequenceNode == NULL)
        {
            return NULL;
        }
        else
        {
            // �r���Ȃ炻������n�߂�
            return SequenceBack(sequenceNode, boss, data);
        }

    }
    // ���s�͏I������
    else if(state == ActionBase::State::FAILED)
    {
        return NULL;
    }

    return nullptr;
}
