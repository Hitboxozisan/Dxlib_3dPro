#include "common.h"
#include "SceneManager.h"

#include "SceneTitle.h"
#include "SceneGame.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
	:eachScenes()
	,currentPointer(nullptr)
	,currentScene()
	,nextScene()
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void SceneManager::Initialize()
{
	eachScenes[TITLE] = new SceneTitle(this);
	eachScenes[GAME_MAIN] = new SceneGame(this);
	//eachScenes[RESULT] = new Result(this);

	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScenes[i]->Initialize();
	}

	// �{����TITLE
	currentScene = nextScene = TITLE;
#if DEBUG
	currentScene = nextScene = GAME_MAIN;
#endif

	currentPointer = eachScenes[currentScene];
	currentPointer->Activate();
}

void SceneManager::Finalize()
{
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScenes[i]->Finalize();
		delete eachScenes[i];
		eachScenes[i] = nullptr;
	}
}

void SceneManager::Update()
{
	if (currentScene != nextScene)
	{
		ChangeScene();		//���̃V�[��
	}

	if (currentPointer != nullptr)
	{
		currentPointer->Update();	//���݂̃V�[���̍X�V����
	}
}

void SceneManager::Draw()
{
	if (currentPointer != nullptr)
	{
		currentPointer->Draw();		//���݂̃V�[���̕`�揈��
	}
}

void SceneManager::SetNextScene(Scene next)
{
	nextScene = next;
}

void SceneManager::ChangeScene()
{
	if (nextScene == END)
	{
		return;
	}


	currentPointer->Deactivate();
	currentPointer = eachScenes[nextScene];
	currentScene = nextScene;
	currentPointer->Activate();
}