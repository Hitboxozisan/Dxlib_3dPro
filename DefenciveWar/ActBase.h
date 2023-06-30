#pragma once
class ActBase
{
public:
	ActBase(class BossEnemy* inEnemy);
	virtual ~ActBase();


	enum class State
	{
		Complete,	// ���s����
		Run,		// ���s��
		Failed,		// ���s���s
	};

	virtual State Run() = 0;
protected:
	BossEnemy* enemy;

private:

};

