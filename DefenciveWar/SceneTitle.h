#pragma once

#include "SceneBase.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class SceneTitle final : public SceneBase
{
public:
	SceneTitle(SceneManager* const sceneManager);
	~SceneTitle();

	enum class State
	{
		DEMO,
		START,
	};

	enum class SelectState
	{
		START,
		OPTION,
		NORMAL,
		HARD,
		SOUND_BGM,
		SOUND_SE,
	};

	void Initialize();	//����������
	void Finalize();	//�I������
	void Activate();	//����������
	void Deactivate();	//�񊈐�������
	void Update();		//�X�V����
	void Draw();		//�`�揈��

private:
	// �I�����ڕ`��ʒu
	const VECTOR START_SELECT_POSITION = VGet(500.0f, 600.0f, 0.0f);
	const VECTOR OPTION_POSITION = VGet(500.0f, 800.0f, 0.0f);
	const VECTOR SELECT_LEVEL_POSITION = VGet(400.0f, 600.0f, 0.0f);
	const VECTOR SELECT_LEVEL_NORMAL_POSITION = VGet(400.0f, 800.0f, 0.0f);
	const VECTOR SELECT_LEVEL_HARD_POSITION = VGet(1000.0f, 800.0f, 0.0f);
	const VECTOR SOUND_OPTION_POSITION = VGet(400.0f, 600.0f, 0.0f);
	const VECTOR SOUND_BGM_POSITION = VGet(400.0f, 750.0f, 0.0f);
	const VECTOR SOUND_SE_POSITION = VGet(400.0f, 850.0f, 0.0f);
	const VECTOR SOUND_BGM_VOLUME_POSITION = VGet(800.0f, 750.0f, 0.0f);
	const VECTOR SOUND_SE_VOLUME_POSITION = VGet(800.0f, 850.0f, 0.0f);

	static const int BLINKING_TIMES;				// �Q�[���J�n���̃A�C�R���_�ŉ�
	const int MAX_VOLUME = 10;						// �ő剹��

	class ScreenBand* screenBand;
	class SoundManager& soundMgr;
	class Font& font;
	class KeyManager& key;
	class ImageManager& imageMgr;

	State state;
	SelectState selectState;

	void DrawSelectMode();							// �I�����ڂ�`��
	void SelectLevel();								// �Q�[����Փx��I��
	void StartGame();								// �Q�[�����J�n����
	void SelectMode();								// ���ڂ�I��
	void SelectSound(int keyCode);					// �Q�[���T�E���h��ݒ�

	// �e�{�^�����������ۂ̍��ڑJ��
	void PushUpButtonState();
	void PushDownButtonState();
	void PushRightButtonState();
	void PushLeftButtonState();
	void PushEnterButoonState();
	void PushBackButtonState();

	int movieHandle;
	int titleImageHandle;
	int alpha;
	int prevAlpha;
	int alphaAdd;
	bool isStartGame;			// �Q�[�����J�n������
};

