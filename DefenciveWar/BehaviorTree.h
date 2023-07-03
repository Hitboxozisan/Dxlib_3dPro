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
	class NodeBase* SelectNode(class NodeBase* inNode, std::vector<NodeBase*> inChild);
	bool SearchNode(std::string inName);
	bool IsUsedNode(NodeBase* inNode);
	NodeBase* InferenceNode();
	void ResetUsedNode();
private:

	class Random& random;

	NodeBase* curretNode;
	std::vector<NodeBase*> aiTree;			// ビヘイビアツリー
	std::vector<NodeBase*> usedNode;		// 使用済みノード
};

