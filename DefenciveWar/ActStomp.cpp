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
 
    // �ڐG�����ꍇ�͐ڐG�������s�����㌋�ʂ�Ԃ�
    if (enemy->IsHit())
    {
        if (enemy->Bounding())
        {
            return ActBase::State::Failed;
        }
    }
    // �ڐG���Ă��Ȃ��Ԃ͍U���s�����J��Ԃ�
    else
    {
        if (enemy->AttackStomp())
        {
            return ActBase::State::Complete;
        }
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

bool ActStomp::HitTarget()
{
    return false;
}
