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

	virtual State Run() = 0;			// 実行
	virtual bool IsExecutabel() = 0;	// 実行可能か
	virtual bool IsContinue() = 0;		// 実行を続けるか
protected:
	BossEnemy* enemy;

private:

};

