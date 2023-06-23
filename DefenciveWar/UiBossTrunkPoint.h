#pragma once

#include "UiBase.h"

class UiBossTrunkPoint final : public UiBase
{
public:
	UiBossTrunkPoint(class SceneGame* objData);
	~UiBossTrunkPoint();

	void Initialize();
	void Update();
	void Draw();

private:

};

