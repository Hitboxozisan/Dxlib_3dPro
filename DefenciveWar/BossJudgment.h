#pragma once

#include "ExecJudgmentBase.h"

/// <summary>
/// BossEnemyビヘイビア行動判断クラス
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

	bool AssaultJudg();			// 突進攻撃可能か
	bool BulletNormalJudg();	// 弾（１発ずつ）を発射可能か
};

