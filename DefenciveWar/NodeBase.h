#pragma once

#include <string>
#include "NodeManager.h"

/// <summary>
/// �r�w�C�r�A�m�[�h���N���X
/// </summary>
class NodeBase
{
public:
	NodeBase(std::string inName, std::string inParent, int inPriority);
	virtual ~NodeBase();

	enum class State
	{
		COMPLETE,	// ���s����
		RUN,		// ���s��
		FAILED,		// ���s���s
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
	std::string name;			// ���O
	std::string parent;			// �e�̃m�[�h�̖��O
	SelectionRule rule;			// �q�̑I����@
	int hierarchy;				// �ǂ̊K�w�ɏ������Ă��邩
	int priority;				// �D��x

private:

};

