#pragma once

#include "ActionBase.h"

class ActionAssault final : public ActionBase
{
public:
	static ActionAssault* GetInstance()
	{
		static ActionAssault instance;
		return &instance;
	}

	virtual State Run(class BossEnemy* boss);

private:
};

