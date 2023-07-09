#pragma once

#include "ActBase.h"

class ActBulletNormal final : public ActBase
{
public:
	ActBulletNormal(class BossEnemy* inEnemy);
	~ActBulletNormal();

	State Run();
	bool IsExecutabel();
	bool IsContinue();

private:
	bool HitTarget();
};

