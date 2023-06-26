#include "common.h"
#include "UiManager.h"
#include "UiBase.h"
#include "UiHitPoint.h"
#include "UiBossTrunkPoint.h"
#include "UiShieldStanpoint.h"

UiManager::UiManager()
{
	
}

UiManager::~UiManager()
{
}

void UiManager::CreateUi(class SceneGame* objData)
{
	// �e��Ui�C���X�^���X����
	EntryUi(new UiHitPoint(objData));
	EntryUi(new UiShieldStanpoint(objData));
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
/// �Q�[���V�[���̍X�V����
/// </summary>
void UiManager::Update()
{
	// �eUi�X�V����
	for (auto itr : ui)
	{
		itr->Update();
	}
}

void UiManager::Draw()
{
	// �eUi�`�揈��
	for (auto itr : ui)
	{
		itr->Draw();
	}
}

void UiManager::EntryUi(UiBase* entryUi)
{
	ui.push_back(entryUi);
}
