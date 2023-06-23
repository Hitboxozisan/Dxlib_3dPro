#include "BossJudgment.h"
#include "BossEnemy.h"
#include "Singleton.h"
#include "Random.h"

using namespace BossState;

BossJudgment::BossJudgment()
	:random(Singleton<Random>::GetInstance())
{
}

BossJudgment::~BossJudgment()
{
}

bool BossJudgment::Judgment(BossEnemy* boss)
{
	// Slide状態じゃない場合は攻撃に移る
	if (boss->GetState() == State::Slide)
	{
		return false;
	}

	if (AssaultJudg())
	{
		return true;
	}
	if (BulletNormalJudg())
	{
		return true;
	}

	return false;
}

/// <summary>
/// 突進攻撃可能か
/// </summary>
/// <returns></returns>
bool BossJudgment::AssaultJudg()
{
	int rand = random.GetRandomInt(0, 100);
	// 指定値より高ければ行動可能とする
	if (rand <= 100)
	{
		return true;
	}

	return false;
}

bool BossJudgment::BulletNormalJudg()
{
	int rand = random.GetRandomInt(0, 100);
	// 指定値より高ければ行動可能とする
	if (rand <= 50)
	{
		return true;
	}


	return false;
}
