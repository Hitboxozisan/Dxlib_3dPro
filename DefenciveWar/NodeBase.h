#pragma once

#include <string>
#include "BehaviorTree.h"
#include "ActBase.h"

/// <summary>
/// ビヘイビアノード基底クラス
/// </summary>
class NodeBase
{
public:
	NodeBase(std::string inName, 
			 int inHierarchy,
			 int inPriority,
			 BehaviorTree::SelectRule inRule,
			 class ActBase* inAction);
	~NodeBase();

	//virtual void Initialize() = 0;
	ActBase::State Update();
	bool IsExecutabel();
	void EntryChild(NodeBase* inNode) { child.push_back(inNode); }

	const std::string GetName() { return name; }
	//const std::string GetParent() { return parent; }
	const BehaviorTree::SelectRule GetRule() { return rule; }
	const int GetHierarchy() { return hierarchy; }
	const int GetPriority() { return priority; }
	ActBase* GetAction() { return action; }
	const bool GetChildEmpty() { return child.empty(); }
	std::vector<NodeBase*> GetChild() { return child; }

	class ActBase* action;					// 行動実行
protected:
	std::string name;						// 名前
	//NodeBase* parent;						// 親のノード
	NodeBase* parent;						// 親のノード
	BehaviorTree::SelectRule rule;			// 子の選択方法
	int hierarchy;							// どの階層に所属しているか
	int priority;							// 優先度

	std::vector<NodeBase*> child;			// ノードの子を収納

private:

};

