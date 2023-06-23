#include "ActionShotBulletNormal.h"
#include "BossEnemy.h"

ActionBase::State ActionShotBulletNormal::Run(BossEnemy* boss)
{
    // �e�𔭎˂���
    if (boss->AttackShotBullet())
    {
        return COMPLETE;
    }

    return ActionBase::State::RUN;
}
