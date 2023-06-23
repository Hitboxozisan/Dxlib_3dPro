#pragma once

#include <string>

class BehaviorTree
{
public:
	// 選択ルール
	enum class SelectRule
	{
		None,
		Priority,			// 優先順位
		Sequence,			// シーケンス
		SequentialLooping,	// シーケンシャルルーピング
		Random,				// ランダム
		OnOff,				// オン・オフ
	};

	void Initialize();
	class NodeBase* Inference(class BossEnemy* boss, class BehaviorData* data);

	// シーケンスノードから推論
	NodeBase* SequenceBack(NodeBase* sequenceNode, BossEnemy* boss, BehaviorData* data);

	// ノード追加
	void AddNode(std::string searchName, std::string entryName, int priority, SelectRule rule, class ExecJudgmentBase* judgment, class ActionBase* action);

	// 実行処理
	NodeBase* Run(BossEnemy* boss, NodeBase* action, BehaviorData* data);
private:
	NodeBase* root;			// ルートノード
};

