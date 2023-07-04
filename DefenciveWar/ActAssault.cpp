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
	if (enemy->AttackAssault())
	{
		return ActBase::State::Complete;
	}
	if (enemy->IsHit())
	{
		return ActBase::State::Failed;
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
