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
/// Àsˆ—
/// </summary>
/// <returns></returns>
ActAssault::State ActAssault::Run()
{
	// ÚG‚µ‚½ê‡‚ÍÚGˆ—‚ğs‚Á‚½ŒãŒ‹‰Ê‚ğ•Ô‚·
	if (enemy->IsHit())
	{
		if (enemy->Sliding())
		{
			return ActBase::State::Failed;
		}
	}
	// ÚG‚µ‚Ä‚¢‚È‚¢ŠÔ‚ÍUŒ‚s“®‚ğŒJ‚è•Ô‚·
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
/// Às‰Â”\‚©
/// </summary>
/// <returns></returns>
bool ActAssault::IsExecutabel()
{
	return true;
}

/// <summary>
/// Às‚ğ‘±‚¯‚é‚©
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
