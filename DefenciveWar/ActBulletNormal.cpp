#include "ActBulletNormal.h"
#include "BossEnemy.h"

ActBulletNormal::ActBulletNormal(BossEnemy* inEnemy)
    :ActBase(inEnemy)
{
}

ActBulletNormal::~ActBulletNormal()
{
}

ActBase::State ActBulletNormal::Run()
{
    if (enemy->AttackShotBullet(true))
    {
        return ActBase::State::Complete;
    }
    if (enemy->IsHit())
    {
        return ActBase::State::Failed;
    }

    return ActBase::State::Run;
}

bool ActBulletNormal::IsExecutabel()
{
    return true;
}

bool ActBulletNormal::IsContinue()
{
    return true;
}


bool ActBulletNormal::HitTarget()
{


    return false;
}
