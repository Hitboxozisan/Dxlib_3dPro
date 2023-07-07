#include "ActStomp.h"
#include "BossEnemy.h"

ActStomp::ActStomp(BossEnemy* inEnemy)
    :ActBase(inEnemy)
{
}

ActStomp::~ActStomp()
{
}

ActBase::State ActStomp::Run()
{
    if (enemy->AttackStomp())
    {
        return ActBase::State::Complete;
    }

    if (enemy->IsHit())
    {
        return ActBase::State::Failed;
    }

    return ActBase::State::Run;
}

bool ActStomp::IsExecutabel()
{
    return true;
}

bool ActStomp::IsContinue()
{
    return true;
}
