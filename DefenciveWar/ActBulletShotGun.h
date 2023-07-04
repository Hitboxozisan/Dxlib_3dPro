#pragma once

#include "ActBase.h"

class ActBulletShotGun final : public ActBase
{
public:
	ActBulletShotGun(class BossEnemy* inEnemy);
	~ActBulletShotGun();

	State Run();
	bool IsExecutabel();
	bool IsContinue();
private:

};

