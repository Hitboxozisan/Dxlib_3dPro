#pragma once

#include <string>
#include "BehaviorTree.h"

/// <summary>
/// ビヘイビアノード基底クラス
/// </summary>
class NodeBase
{
public:
	NodeBase(std::string inName, 
			 std::string inParent, 
			 int inHierarchy,
			 int inPriority,
			 BehaviorTree::SelectRule inRule,
			 class ActBase* inAction);
	~NodeBase();

	//virtual void Initialize() = 0;
	void Update();
	bool IsExecutabel();

	const std::string GetName() { return name; }
	const std::string GetParent() { return parent; }
	const BehaviorTree::SelectRule GetRule() { return rule; }
	const int GetHierarchy() { return hierarchy; }
	const int GetPriority() { return priority; }
	const ActBase* GetAction() { return action; }

protected:
	std::string name;						// 名前
	//NodeBase* parent;						// 親のノード
	std::string parent;						// 親のノード名
	BehaviorTree::SelectRule rule;			// 子の選択方法
	int hierarchy;							// どの階層に所属しているか
	int priority;							// 優先度
	class ActBase* action;					// 行動実行

	std::vector<NodeBase*>* child;			// ノードの子を収納

private:

};

