#pragma once

#include "ActBase.h"

class ActStomp final : public ActBase
{
public:
	ActStomp(class BossEnemy* inEnemy);
	~ActStomp();

	State Run();
	bool IsExecutabel();
	bool IsContinue();

private:
	bool HitTarget();
};

