#include "BehaviorData.h"
#include "NodeBase.h"

BehaviorData::BehaviorData()
{
	// シーケンスを削除
	Initialize();
}

BehaviorData::~BehaviorData()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void BehaviorData::Initialize()
{
	// 実行シーケンスのステップマップをリセット
	runSequnceStepMap.clear();
	// シーケンスノードスタックを削除
	while (sequenceStack.size() > 0)
	{
		sequenceStack.pop();
	}
}

/// <summary>
/// シーケンスノードのポップ
/// </summary>
/// <returns></returns>
NodeBase* BehaviorData::PopSequneceNode()
{
	// 空ならNULL
	if (sequenceStack.empty() != 0)
	{
		return NULL;
	}

	NodeBase* node = sequenceStack.top();

	if (node != NULL)
	{
		// 取り出したデータを削除
		sequenceStack.pop();
	}

	return node;
}

/// <summary>
/// 現在のシーケンスステップの取得
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
int BehaviorData::GetSequenceStep(std::string name)
{
	return 0;
}

bool BehaviorData::IsNodeUsed(std::string name)
{
	// 使用してなかったらfalse
	if (usedNodeMap.count(name) == 0)
	{
		return false;
	}

	return usedNodeMap[name];
}

/// <summary>
/// 使用ノードのリセット
/// </summary>
/// <param name="reset_hierachy"></param>
void BehaviorData::ResetNodeUsed(std::vector<NodeBase*>* reset_hierachy)
{
	for (auto itr = reset_hierachy->begin(); itr != reset_hierachy->end(); itr++)
	{
		usedNodeMap[(*itr)->GetName()] = false;
	}
}
