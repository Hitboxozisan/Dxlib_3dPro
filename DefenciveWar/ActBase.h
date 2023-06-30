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
		Failed,		// Às¸”s
	};

	virtual State Run() = 0;
protected:
	BossEnemy* enemy;

private:

};

