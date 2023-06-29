#pragma once

/// <summary>
/// 
/// </summary>
class BehaviorManager final
{
public:
	BehaviorManager();
	~BehaviorManager();

	void Initialize();
	void Update();
	void EntryNode(class NodeBase* inNode);

private:
	class BehaviorTree* aiTree;
};

