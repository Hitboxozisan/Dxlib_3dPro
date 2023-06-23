#pragma once

#include<string>

/// <summary>
/// �T�E���h�Ǘ��N���X
/// �V���O���g��
/// </summary>
class SoundManager final
{
public:
	SoundManager();
	~SoundManager();

	enum Bgm
	{
		MAIN,
		RESULT,

		BGM_AMOUNT
	};

	
	enum Se
	{
		CHARACTER_HIT = 0,			// �ڐG��
		SHOOT_BULLET_PLAYER,		// ���ˉ��i�v���C���[�j
		SHOOT_BULLET_ENEMY,			// ���ˉ��i�G�l�~�[�j
		SHIELD_HIT_NORMAL,			// �h�䉹�i�ʏ�j
		SHIELD_HIT_JUST,			// �h�䉹�i�W���X�g�j
		SHIELD_HIT_BULLET = 5,		// �h�䉹�i�e�j
		HIT_BULLET_PLAYER,			// �e��e���i�v���C���[�j
		HIT_BULLET_ENEMY,			// �e��e���i�G�l�~�[�j
		SHIELD_BREAK,				// �V�[���h�j��
		PLAYER_DIE,					// �v���C���[���S��
		ENEMY_DIE = 10,				// �G�l�~�[���S��
		PINCH_HITPOINT,				// HitPoint�댯��
		TELEPORT_ENEMY,				// �e���|�[�g���i�G�l�~�[�j
		ACTIVE_SHIELD,				// �V�[���h�W�J��
		DECIDE_SCORE,				// �X�R�A�m�艹
		AVOIDANCE_PLAYER = 15,		// ������i�v���C���[�j
		PUSH_START,					// �Q�[���J�n��
		RECOVERY_PLAYER,			// �񕜉��i�v���C���[�j
		SOUND_SE_TEST,				// �I�v�V����SE�ݒ艹
		SELECT,						// ���ڑI����

		SE_AMOUNT					// SE����
	};

	void Update();

	void PlayBgm(Bgm bgm, bool loop = true);
	void StopBgm();

	// �Z�b�^�[
	void SetSePlayFlag(Se se);
	void SetBgmVolume(int volume);
	void SetSeVolume(int volume);
	// �Q�b�^�[
	const int GetBgmVolume() const { return BGM_VOLUME; }
	const int GetSeVolume() const { return SE_VOLUME; }

private:

	void LoadAllSound();
	void DeleteAllSound();

	void VolumeChange();
	//�萔
	static const std::string SOUND_FOLDER_PATH;  // Sound�t�H���_�܂ł̃p�X
	static const std::string BGM_PATH;           // BGM�t�@�C����(�A�ԏ���)
	static const std::string SE_PATH;            // SE�t�@�C����(�A�ԏ���)
	static const std::string BGM_FILENAME_EXTENSION; // BGM�g���q
	static const std::string SE_FILENAME_EXTENSION;  // SE�g���q

	int BGM_VOLUME;                 // BGM�̉���
	int SE_VOLUME;                  // SE�̉���


	int  bgmData[BGM_AMOUNT];  // BGM�ǂݍ��ݗp
	int  seData[SE_AMOUNT];    // SE�ǂݍ��ݗp
	bool sePlayFlag[SE_AMOUNT];// ���̃t���[���ōĐ����邩
};

