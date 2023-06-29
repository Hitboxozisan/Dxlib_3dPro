#pragma once

#include <map>
#include <vector>
#include "NodeBase.h"

/// <summary>
/// ビヘイビアツリー本体
/// </summary>
class BehaviorTree final
{
public:
	BehaviorTree();
	~BehaviorTree();

	// 選択ルール
	enum class SelectionRule
	{
		NONE,			// なし（末端ノード）
		Priority,		// 優先順
		Sequence,		// シークエンス
		Random,			// ランダム
	};

	void Initialize();
	void EntryNode(class NodeBase* inNode);
	bool SearchNode(std::string inName);
	void Reset();

private:
	std::vector<NodeBase*>* aiTree;
};

