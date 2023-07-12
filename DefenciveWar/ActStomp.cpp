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
 
    // ÚG‚µ‚½ê‡‚ÍÚGˆ—‚ðs‚Á‚½ŒãŒ‹‰Ê‚ð•Ô‚·
    if (enemy->IsHit())
    {
        if (enemy->Bounding())
        {
            return ActBase::State::Failed;
        }
    }
    // ÚG‚µ‚Ä‚¢‚È‚¢ŠÔ‚ÍUŒ‚s“®‚ðŒJ‚è•Ô‚·
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
