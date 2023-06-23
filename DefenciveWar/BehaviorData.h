#pragma once

#include <vector>
#include <stack>
#include <map>

#include "BehaviorTree.h"

class BehaviorData
{
public:
	BehaviorData();
	~BehaviorData();

	void Initialize();
	void ResetNodeUsed(std::vector<NodeBase*>* reset_hierachy);				// 使用済みノードのリセット
	void EntryUsedNode(std::string name) { usedNodeMap[name] = true; };		// 使用済みノードに登録					// 使用済みノードに登録

	class NodeBase* PopSequneceNode();
	void PushSequenceNode(NodeBase* node) { sequenceStack.push(node); };
	int GetSequenceStep(std::string name);			// シーケンスステップのゲッター
	bool IsNodeUsed(std::string name);

	void SetSequenceStep(std::string name, int step) { runSequnceStepMap[name] = step; };

private:
	std::stack<class NodeBase*> sequenceStack;		// シーケンスノードスタック
	std::map<std::string, int> runSequnceStepMap;	// 実行シーケンスのステップマップ
	std::map<std::string, bool> usedNodeMap;		// 使用済みノードマップ
};

