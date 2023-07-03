#pragma once
class ActBase
{
public:
	ActBase(class BossEnemy* inEnemy);
	virtual ~ActBase();


	enum class State
	{
		Complete,	// ÀsŠ®—¹
		Run,		// Às’†
		Failed,		// ’†’f‚³‚ê‚½
	};

	virtual State Run() = 0;
	virtual bool IsExecutabel() = 0;
	virtual bool IsContinue() = 0;
protected:
	BossEnemy* enemy;

private:

};

