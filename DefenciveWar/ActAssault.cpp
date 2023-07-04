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
/// 実行処理
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
/// 実行可能か
/// </summary>
/// <returns></returns>
bool ActAssault::IsExecutabel()
{
	return true;
}

/// <summary>
/// 実行を続けるか
/// </summary>
/// <returns></returns>
bool ActAssault::IsContinue()
{
	return true;
}
