#pragma once
class ActBase
{
public:
	ActBase(class BossEnemy* inEnemy);
	virtual ~ActBase();


	enum class State
	{
		Complete,	// 実行完了
		Run,		// 実行中
		Failed,		// 中断された
	};

	virtual State Run() = 0;
	virtual bool IsExecutabel() = 0;
	virtual bool IsContinue() = 0;
protected:
	BossEnemy* enemy;

private:

};

