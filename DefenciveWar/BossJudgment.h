#pragma once

#include "ExecJudgmentBase.h"

/// <summary>
/// BossEnemy�r�w�C�r�A�s�����f�N���X
/// </summary>
class BossJudgment final : public ExecJudgmentBase
{
public:
	BossJudgment();
	~BossJudgment();
	// 
	static BossJudgment* GetInstance()
	{
		static BossJudgment instance;
		return &instance;
	}

	virtual bool Judgment(class BossEnemy* boss);
private:

	class Random& random;

	bool AssaultJudg();			// �ːi�U���\��
	bool BulletNormalJudg();	// �e�i�P�����j�𔭎ˉ\��
};

