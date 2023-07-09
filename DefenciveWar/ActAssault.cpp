//#include "ActBase.h"
#include "ActAssault.h"
#include "BossEnemy.h"

ActAssault::ActAssault(class BossEnemy* inEnemy)
	:ActBase(inEnemy)
{
}

ActAssault::~ActAssault()
{
}

/// <summary>
/// ���s����
/// </summary>
/// <returns></returns>
ActAssault::State ActAssault::Run()
{
	// �ڐG�����ꍇ�͐ڐG�������s�����㌋�ʂ�Ԃ�
	if (enemy->IsHit())
	{
		if (enemy->Sliding())
		{
			return ActBase::State::Failed;
		}
	}
	// �ڐG���Ă��Ȃ��Ԃ͍U���s�����J��Ԃ�
	else
	{
		if (enemy->AttackAssault())
		{
			return ActBase::State::Complete;
		}
	}

	return ActBase::State::Run;
}

/// <summary>
/// ���s�\��
/// </summary>
/// <returns></returns>
bool ActAssault::IsExecutabel()
{
	return true;
}

/// <summary>
/// ���s�𑱂��邩
/// </summary>
/// <returns></returns>
bool ActAssault::IsContinue()
{
	return true;
}

bool ActAssault::HitTarget()
{
	return false;
}
