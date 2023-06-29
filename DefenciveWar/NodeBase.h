#pragma once

#include <string>
#include "NodeManager.h"

/// <summary>
/// ビヘイビアノード基底クラス
/// </summary>
class NodeBase
{
public:
	NodeBase(std::string inName, std::string inParent, int inPriority);
	virtual ~NodeBase();

	enum class State
	{
		COMPLETE,	// 実行完了
		RUN,		// 実行中
		FAILED,		// 実行失敗
	};

	//virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual bool IsExecutabel() = 0;

	const State GetState() { return state; }
	const std::string GetName() { return name; }
	const std::string GetParent() { return parent; }
	const SelectionRule GetRule() { return rule; }
	const int GetHierarchy() { return hierarchy; }
	const int GetPriority() { return priority; }

protected:
	State state;
	std::string name;			// 名前
	std::string parent;			// 親のノードの名前
	SelectionRule rule;			// 子の選択方法
	int hierarchy;				// どの階層に所属しているか
	int priority;				// 優先度

private:

};

