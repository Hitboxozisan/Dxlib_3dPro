#include "ActionAssault.h"
#include "BossEnemy.h"

ActionBase::State ActionAssault::Run(BossEnemy* boss)
{
    if (boss->AttackAssault())
    {
        return ActionBase::State::COMPLETE;
    }

    if (boss->GetState() == BossState::State::Slide)
    {
        return ActionBase::State::FAILED;
    }

    return ActionBase::State::RUN;
}
