#pragma once

#include <map>
#include <vector>
#include <string>
#include <stack>

/// <summary>
/// ビヘイビアツリー本体
/// </summary>
class BehaviorTree final
{
public:
	BehaviorTree();
	~BehaviorTree();

	// 選択ルール
	enum class SelectRule
	{
		None,			// なし（末端ノード）
		Priority,		// 優先順
		Sequence,		// シークエンス
		Random,			// ランダム
	};

	void Initialize();
	void EntryNode(std::string inName, 
				   std::string inParent, 
				   int inHierarchy, 
				   int inPriority,
				   BehaviorTree::SelectRule inRule, 
				   class ActBase* inAction);
	class NodeBase* SelectNode(class NodeBase* inNode);
	bool SearchNode(std::string inName);
	bool IsUsedNode(NodeBase* inNode);
	NodeBase* SequenceEnRoute();
	NodeBase* InferenceNode();
	void ResetUsedNode();

	NodeBase* SelectPriority();
	NodeBase* SelectSequence(NodeBase* inParent);
	NodeBase* SelectRandom();
private:

	class Random& random;

	std::vector<NodeBase*> aiTree;			// ビヘイビアツリー
	std::vector<NodeBase*> activeNode;		// 実行可能ノード
	std::vector<NodeBase*> usedNode;		// 使用済みノード
	std::stack<NodeBase*> sequenceNode;		// シークエンスノード
};

