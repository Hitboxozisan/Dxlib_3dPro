#pragma once

#include <map>
#include <vector>
#include <string>

/// <summary>
/// ビヘイビアツリー本体
/// </summary>
class BehaviorTree final
{
public:
	BehaviorTree();
	~BehaviorTree();

	// 選択ルール
	enum SelectRule
	{
		None,			// なし（末端ノード）
		Priority,		// 優先順
		Sequence,		// シークエンス
		Selector,		// セレクター
		Random,			// ランダム
	};

	void Initialize();
	void EntryNode(class NodeBase* inNode);
	bool SearchNode(std::string inName);
	bool IsUsedNode(NodeBase* inNode);
	NodeBase* InferenceNode();
	void ResetUsedNode();
private:
	std::vector<NodeBase*>* aiTree;			// ビヘイビアツリー
	std::vector<NodeBase*>* usedNode;		// 使用済みノード
};

