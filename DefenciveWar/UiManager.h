#pragma once

#include "ImageTypeData.h"

class UiManager
{
public:
	UiManager();
	~UiManager();

	void CreateUi(class SceneGame* objData);
	void Initialize();
	void Update();
	void Draw();
	void EntryUi(class UiBase* entryUi);

private:
	std::vector<UiBase*> ui;
};

