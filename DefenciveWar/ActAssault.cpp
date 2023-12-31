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
	// 接触した場合は接触処理を行った後結果を返す
	if (enemy->IsHit())
	{
		if (enemy->Sliding())
		{
			return ActBase::State::Failed;
		}
	}
	// 接触していない間は攻撃行動を繰り返す
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

bool ActAssault::HitTarget()
{
	return false;
}
