#include "common.h"
#include "SoundManager.h"

using std::string;

const string SoundManager::SOUND_FOLDER_PATH = "Data/Sound/";
const string SoundManager::BGM_PATH = "Bgm";
const string SoundManager::SE_PATH = "Se";
const string SoundManager::BGM_FILENAME_EXTENSION = ".mp3";
const string SoundManager::SE_FILENAME_EXTENSION = ".mp3";

//const int SoundManager::SE_VOLUME = 255 * 80 / 100;
//const int SoundManager::BGM_VOLUME = 255 * 50 / 100;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SoundManager::SoundManager()
	:bgmData()
	, seData()
	, sePlayFlag()
    , SE_VOLUME(80)
    , BGM_VOLUME(50)
{
	LoadAllSound();
	VolumeChange();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SoundManager::~SoundManager()
{
    DeleteAllSound();
}

/// <summary>
/// �X�V����
/// </summary>
void SoundManager::Update()
{
    // �o�^���ꂽ���ʉ����Đ�
    for (int i = 0; i < SE_AMOUNT; ++i)
    {
        // �o�^����Ă��Ȃ�
        if (sePlayFlag[i] == false)
        {
            continue;
        }

        // �������������ɍĐ����Ȃ特�ʂ�0�ɂ��Ē�~
        if (CheckSoundMem(seData[i]) != 0)   // �߂�l��int
        {
            ChangeVolumeSoundMem(0, seData[i]);
            StopSoundMem(seData[i]);
            ChangeVolumeSoundMem(SE_VOLUME, seData[i]);
        }
        PlaySoundMem(seData[i], DX_PLAYTYPE_BACK, TRUE); // �Đ�
        sePlayFlag[i] = false;
    }
}

void SoundManager::PlayBgm(Bgm bgm, bool loop)
{
    if (loop == true)
    {
        PlaySoundMem(bgmData[bgm], DX_PLAYTYPE_LOOP, TRUE);
    }
    else
    {
        PlaySoundMem(bgmData[bgm], DX_PLAYTYPE_BACK, TRUE);
    }
}

void SoundManager::StopBgm()
{
    for (int i = 0; i < BGM_AMOUNT; ++i)
    {
        StopSoundMem(bgmData[i]);
    }
}

void SoundManager::SetSePlayFlag(Se se)
{
    sePlayFlag[se] = true;
}

void SoundManager::SetBgmVolume(int volume)
{
    BGM_VOLUME = 255 * (10 * volume) / 100;
    VolumeChange();
}

void SoundManager::SetSeVolume(int volume)
{
    SE_VOLUME = 255 * (10 * volume) / 100;
    VolumeChange();
}

/// <summary>
/// �S�ẴT�E���h�̓ǂݍ���
/// </summary>
void SoundManager::LoadAllSound()
{
    // BGM�f�[�^�ǂݍ���
    string path = SOUND_FOLDER_PATH + BGM_PATH; // �t�H���_�p�X + �t�@�C����
    string fullPath = path;
    for (int i = 0; i < BGM_AMOUNT; ++i)
    {
        fullPath = path + std::to_string(i) + BGM_FILENAME_EXTENSION; // + �A�Ԑ��� + .�g���q
        bgmData[i] = LoadSoundMem(fullPath.c_str());

        if (bgmData[i] < 0)
        {
            printfDx("�����ǂݍ��݂Ɏ��s_SoundManager_bgm[%d]\n", i);
            bgmData[i] = 0;
        }
    }


    path = SOUND_FOLDER_PATH + SE_PATH; // �t�H���_�p�X + �t�@�C����
    fullPath = path;
    for (int i = 0; i < SE_AMOUNT; ++i)
    {
        fullPath = path + std::to_string(i) + SE_FILENAME_EXTENSION; // + �A�Ԑ��� + .�g���q
        seData[i] = LoadSoundMem(fullPath.c_str());

        if (seData[i] < 0)
        {
            printfDx("�����ǂݍ��݂Ɏ��s_SoundManager_se[%d]\n", i);
            seData[i] = 0;
        }
    }
}

void SoundManager::DeleteAllSound()
{
    // BGM
    for (int i = 0; i < BGM_AMOUNT; ++i)
    {
        DeleteSoundMem(BGM_VOLUME, bgmData[i]);
        bgmData[i] = NULL;
    }

    // SE
    for (int i = 0; i < SE_AMOUNT; ++i)
    {
        DeleteSoundMem(SE_VOLUME, seData[i]);
        seData[i] = NULL;
    }
}

void SoundManager::VolumeChange()
{
    // BGM
    for (int i = 0; i < BGM_AMOUNT; ++i)
    {
        ChangeVolumeSoundMem(BGM_VOLUME, bgmData[i]);
    }

    // SE
    for (int i = 0; i < SE_AMOUNT; ++i)
    {
        ChangeVolumeSoundMem(SE_VOLUME, seData[i]);
    }
}