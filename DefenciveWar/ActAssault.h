#pragma once

#include "ActBase.h"

class ActAssault final : public ActBase
{
public:
	ActAssault(class BossEnemy* inEnemy);
	~ActAssault();

	State Run();
private:
};

