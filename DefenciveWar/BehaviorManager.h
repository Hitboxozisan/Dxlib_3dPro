#pragma once

/// <summary>
/// ノードの選択・実行を行う
/// </summary>
class BehaviorManager final
{
public:
	BehaviorManager();
	~BehaviorManager();

	void Initialize();
	void Update();
	
	void EntryNode(class NodeBase* inNode);
	NodeBase* InferenceNode();

private:
	class BehaviorTree* aiTree;
};
