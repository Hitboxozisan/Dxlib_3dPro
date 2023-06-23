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
	// 処理なし
}

NodeBase::~NodeBase()
{
	// 処理なし
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
/// 優先順位選択
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
NodeBase* NodeBase::SelectPriority(std::vector<NodeBase*>* list)
{
	NodeBase* select_node = NULL;
	int priority = -10000;

	// 一番優先順位が高いノードを探す
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
/// ランダム選択
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
NodeBase* NodeBase::SelectRandom(std::vector<NodeBase*>* list)
{
	int selectNo = rand() % list->size();

	return (*list)[selectNo];
}

/// <summary>
/// オン・オフ選択
/// </summary>
/// <param name="list"></param>
/// <param name="data"></param>
/// <returns></returns>
NodeBase* NodeBase::SelectOnOff(std::vector<NodeBase*>* list, BehaviorData* data)
{
	std::vector<NodeBase*> offList;

	// 使用済みノードリストアップする
	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
		if (!data->IsNodeUsed((*itr)->GetName()))
		{
			offList.push_back(*itr);
		}
	}

	// リストアップした数をチェック
	if (offList.size() == 0)
	{
		// ノードを全てリセット
		data->ResetNodeUsed(&child);
		offList = *list;
	}

	// 使用したノードを登録
	data->EntryUsedNode(offList[0]->GetName());

	// リストの先頭が決定ノード
	return offList[0];
}

/// <summary>
/// シーケンス選択
/// </summary>
/// <param name="list"></param>
/// <param name="data"></param>
/// <returns></returns>
NodeBase* NodeBase::SelectSequence(std::vector<NodeBase*>* list, BehaviorData* data)
{
	// 今のノードのシーケンスのステップを取得
	int step = data->GetSequenceStep(GetName());

	// シーケンスが終わってたら終了
	if (step >= child.size())
	{
		if (selectRule != BehaviorTree::SelectRule::SequentialLooping)
		{
			return NULL;
		}
		else {
			// Loopingの場合は頭から実行
			step = 0;
		}
	}

	// 順番のノードが実行できるかのチェック
	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
		if (child[step]->GetName() == (*itr)->GetName())
		{
			// シーケンスノードを記録
			data->PushSequenceNode(this);
			// シーケンスステップを更新
			data->SetSequenceStep(GetName(), step + 1);
			return child[step];
		}
	}

	return NULL;
}

/// <summary>
/// ノード検索
/// </summary>
/// <param name="searchName"></param>
/// <returns></returns>
NodeBase* NodeBase::SearchNode(std::string searchName)
{
	// 名前が一致
	if (name == searchName)
	{
		return this;
	}
	else
	{
		// 子ノードで検索
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
/// ノード推論
/// </summary>
/// <param name="boss"></param>
/// <param name="data"></param>
/// <returns></returns>
NodeBase* NodeBase::Inference(BossEnemy* boss, BehaviorData* data)
{
	std::vector<NodeBase*> list;
	NodeBase* result = NULL;

	// 子ノードで実行可能なノードを探す
	for (int i = 0; i < child.size(); i++)
	{
		// 実行判定がある場合
		if (child[i]->execJudgment != NULL)
		{
			// 実行判定処理
			if (child[i]->execJudgment->Judgment(boss))
			{
				list.push_back(child[i]);
			}
		}
		else
		{
			// 判定処理がなければ無条件に追加
			list.push_back(child[i]);
		}
	}

	// 選択ルールでノードを決定する
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
		// 行動があれば終了
		if (result->HasAction())
		{
			return result;
		}
		else
		{
			// 決まったノードで推論開始
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
