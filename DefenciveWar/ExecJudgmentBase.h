#pragma once

// ���s����
class ExecJudgmentBase
{
public:
	ExecJudgmentBase();
	virtual ~ExecJudgmentBase();

	virtual bool Judgment(class BossEnemy* mover) = 0;
};

