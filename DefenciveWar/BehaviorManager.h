#pragma once

/// <summary>
/// �m�[�h�̑I���E���s���s��
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
