#pragma once

#include <vector>
#include <string>
#include "BehaviorTree.h"
#include "ActionBase.h"

class ExecJudgmentBase;
class BehaviorData;
class BossEnemy;

/// <summary>
/// 
/// </summary>
class NodeBase
{
public:
	NodeBase(std::string inName,
			 NodeBase *inParent,
			 NodeBase *inSibling,
			 int inPriority,
			 BehaviorTree::SelectRule inSelectRule,
			 ExecJudgmentBase* inJudgment,
			 ActionBase* inAction,
			 int inHierarchyNo);
	~NodeBase();

	

	NodeBase* SelectPriority(std::vector<NodeBase*>* list);	// 優先順位選択
	NodeBase* SelectRandom(std::vector<NodeBase*>* list);	// ランダム選択
	NodeBase* SelectOnOff(std::vector<NodeBase*>* list,
						  BehaviorData* data);				// オン・オフ選択
	NodeBase* SelectSequence(std::vector<NodeBase*>* list,
							 BehaviorData* data);			// シーケンス選択
	

	NodeBase* SearchNode(std::string searchName);				// ノード検索
	NodeBase* Inference(BossEnemy* boss, BehaviorData* data);	// ノード推論
	void PrintName();											// ノード名表示

	ActionBase::State Run(BossEnemy* boss);		// 実行
	
	// ゲッター
	std::string GetName() { return name; };			// 名前ゲッター
	NodeBase* GetParent() { return parent; };		// 親ノードゲッター
	NodeBase* GetChild(int idx);					// 子ノードゲッター
	NodeBase* GetLastChild();						// 子ノードゲッター（末尾）
	NodeBase* GetTopChild();						// 子ノードゲッター（先頭）
	NodeBase* GetSibling() { return sibling; };		// 兄弟ノードゲッター
	int GetHirechyNo() { return hierarchyNo; };		// 階層番号ゲッター
	int GetPriority() { return priority; };			// 優先順位ゲッター
	// セッター
	void SetParent(NodeBase* inParent) { parent = inParent; };			// 親ノードゲッター
	void AddChaild(NodeBase* inChild) { child.push_back(inChild); };	// 子ノード追加
	void SetSibling(NodeBase* inSibling) { sibling = inSibling; };		// 兄弟ノードセッター

	bool HasAction() { return action != NULL ? true : false; };			// 行動データを持っているか
	bool Judgment(BossEnemy* boss);			// 実行可否判定

private:
	std::string name;						// 名前
	BehaviorTree::SelectRule selectRule;	// 選択ルール
	ExecJudgmentBase* execJudgment;			// 判定クラス
	ActionBase* action;						// 実行クラス
	unsigned int priority;					// 優先順位
	NodeBase* parent;						// 親ノード
	std::vector<NodeBase*> child;			// 子ノード
	NodeBase* sibling;						// 兄弟ノード
	int hierarchyNo;						// 階層番号

};

