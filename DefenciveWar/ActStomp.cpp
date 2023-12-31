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
 
    // 接触した場合は接触処理を行った後結果を返す
    if (enemy->IsHit())
    {
        if (enemy->Bounding())
        {
            return ActBase::State::Failed;
        }
    }
    // 接触していない間は攻撃行動を繰り返す
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
