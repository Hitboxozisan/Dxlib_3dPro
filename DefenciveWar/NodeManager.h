#pragma once

#include <vector>

// 選択ルール
enum class SelectionRule
{
	NONE,			// なし（末端ノード）
	Priority,		// 優先順
	Sequence,		// シークエンス
	Random,			// ランダム
};

/// <summary>
/// ノードの進行・管理を行う
/// シングルトンではなく各自所持する
/// </summary>
class NodeManager
{
public:
	NodeManager();
	~NodeManager();

	void Initialize();
	void Update();

	void EntryNode(class NodeBase*);
	void EntryUsedNode(NodeBase*);;
	bool SearchUsedNode(NodeBase*);
	NodeBase* DecisionRunNode();
private:

	void RunNode(NodeBase*);

	NodeBase* parent;							// 親のノード
	std::vector<NodeBase*>* tree;				// ノード全体
	std::vector<NodeBase*>* currentNode;		// 現在の階層ノード
	//std::vector<NodeBase*> child;
	std::vector<NodeBase*>* usedNode;
};

