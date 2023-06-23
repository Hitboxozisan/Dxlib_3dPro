#include "common.h"
#include "UiManager.h"
#include "UiBase.h"
#include "UiHitPoint.h"
#include "UiBossTrunkPoint.h"

UiManager::UiManager()
{
	
}

UiManager::~UiManager()
{
}

void UiManager::CreateUi(class SceneGame* objData)
{
	// 各種Uiインスタンス生成
	EntryUi(new UiHitPoint(objData));
	//EntryUi(new UiBossTrunkPoint(objData));
}

void UiManager::Initialize()
{
	for (auto itr : ui)
	{
		itr->Initialize();
	}
}

/// <summary>
/// ゲームシーンの更新処理
/// </summary>
void UiManager::Update()
{
	// 各Ui更新処理
	for (auto itr : ui)
	{
		itr->Update();
	}
}

void UiManager::Draw()
{
	// 各Ui描画処理
	for (auto itr : ui)
	{
		itr->Draw();
	}
}

void UiManager::EntryUi(UiBase* entryUi)
{
	ui.push_back(entryUi);
}
