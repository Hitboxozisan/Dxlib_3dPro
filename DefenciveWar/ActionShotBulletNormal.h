#pragma once

#include "ActionBase.h"

class ActionShotBulletNormal : public ActionBase
{
public:

	static ActionShotBulletNormal* GetInstance()
	{
		static ActionShotBulletNormal instance;
		return&instance;
	}

	virtual State Run(BossEnemy* boss);
};

