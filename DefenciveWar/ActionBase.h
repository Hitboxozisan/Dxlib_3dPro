#pragma once

class ActionBase
{
public:

	// ���s���
	enum State
	{
		RUN,			// ���s��
		FAILED,			// ���s���s
		COMPLETE,		// ���s����
	};

	// ���s����
	virtual State Run(class BossEnemy* boss) = 0;

private:
};

