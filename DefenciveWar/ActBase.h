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

	virtual State Run() = 0;			// ���s
	virtual bool IsExecutabel() = 0;	// ���s�\��
	virtual bool IsContinue() = 0;		// ���s�𑱂��邩
protected:
	BossEnemy* enemy;

private:

};

