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
		Failed,		// ���f���ꂽ
	};

	virtual State Run() = 0;
	virtual bool IsExecutabel() = 0;
	virtual bool IsContinue() = 0;
protected:
	BossEnemy* enemy;

private:

};

