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

ActAssault::State ActAssault::Run()
{
	if (enemy->AttackAssault())
	{
		return ActBase::State::Complete;
	}

	return ActBase::State::Run;
}

bool ActAssault::IsExecutabel()
{
	return true;
}

bool ActAssault::IsContinue()
{
	return true;
}
