#include "ActionShotBulletNormal.h"
#include "BossEnemy.h"

ActionBase::State ActionShotBulletNormal::Run(BossEnemy* boss)
{
    // ’e‚ð”­ŽË‚·‚é
    if (boss->AttackShotBullet())
    {
        return COMPLETE;
    }

    return ActionBase::State::RUN;
}
