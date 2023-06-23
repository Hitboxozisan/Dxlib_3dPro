#include "common.h"
#include "BehaviorTree.h"
#include "BehaviorData.h"
#include "NodeBase.h"

void BehaviorTree::Initialize()
{

}


NodeBase* BehaviorTree::Inference(BossEnemy* boss, BehaviorData* data)
{
    // データをリセットしてから開始
    data->Initialize();
    return root->Inference(boss, data);
}

/// <summary>
/// シーケンスノードから推論
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
/// ノードの追加
/// </summary>
/// <param name="search_name"></param>
/// <param name="entry_name"></param>
/// <param name="priority"></param>
/// <param name="select_rule"></param>
/// <param name="judgment"></param>
/// <param name="action"></param>
void BehaviorTree::AddNode(std::string searchName, std::string entryName, int priority, SelectRule rule, ExecJudgmentBase* judgment, ActionBase* action)
{
    // 検索ノードがある場合
    if (searchName != "")
    {
        // ノードを検索する
        NodeBase* searchNode = root->SearchNode(searchName);

        // ノードが見つかった場合
        if (searchNode != NULL)
        {
            // ノードの末尾を取得
            NodeBase* sibling = searchNode->GetLastChild();
            // 新規ノードを作成
            NodeBase* addNode = new NodeBase(entryName, searchNode, sibling, priority, rule, judgment, action, 1);

            searchNode->AddChaild(addNode);
        }

    }
    // ない場合
    else
    {
        // ルートノードがない場合は新規ルートノードを
        if (root == NULL)
        {
            root = new NodeBase(entryName, NULL, NULL, priority, rule, judgment, action, 1);
        }
        else
        {
            printfDx("ルートは既に登録されています\n");
        }
    }
}

/// <summary>
/// ノードの実行
/// </summary>
/// <param name="boss"></param>
/// <param name="action"></param>
/// <param name="data"></param>
/// <returns></returns>
NodeBase* BehaviorTree::Run(BossEnemy* boss, NodeBase* action, BehaviorData* data)
{
    // ノードの実行
    ActionBase::State state = action->Run(boss);

    // 正常に終了した場合
    if (state == ActionBase::State::COMPLETE)
    {
        // シーケンスの途中かを判断
        NodeBase* sequenceNode = data->PopSequneceNode();

        // 途中じゃないなら終了
        if (sequenceNode == NULL)
        {
            return NULL;
        }
        else
        {
            // 途中ならそこから始める
            return SequenceBack(sequenceNode, boss, data);
        }

    }
    // 失敗は終了する
    else if(state == ActionBase::State::FAILED)
    {
        return NULL;
    }

    return nullptr;
}
