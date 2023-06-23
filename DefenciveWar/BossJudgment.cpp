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
	// Slide��Ԃ���Ȃ��ꍇ�͍U���Ɉڂ�
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
/// �ːi�U���\��
/// </summary>
/// <returns></returns>
bool BossJudgment::AssaultJudg()
{
	int rand = random.GetRandomInt(0, 100);
	// �w��l��荂����΍s���\�Ƃ���
	if (rand <= 100)
	{
		return true;
	}

	return false;
}

bool BossJudgment::BulletNormalJudg()
{
	int rand = random.GetRandomInt(0, 100);
	// �w��l��荂����΍s���\�Ƃ���
	if (rand <= 50)
	{
		return true;
	}


	return false;
}
