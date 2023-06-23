#include "common.h"
#include "KeyManager.h"

#include <chrono>

short KeyManager::stickLX_DeadZoneMAX = 1000;
short KeyManager::stickLX_DeadZoneMIN = -1000;
short KeyManager::stickLY_DeadZoneMAX = 1000;
short KeyManager::stickLY_DeadZoneMIN = -1000;
short KeyManager::stickRX_DeadZoneMAX = 1000;
short KeyManager::stickRX_DeadZoneMIN = -1000;
short KeyManager::stickRY_DeadZoneMAX = 1000;
short KeyManager::stickRY_DeadZoneMIN = -1000;

// VECTOR�̌v�Z�Ɏg�p
using namespace Math3d;

//---------------------------------------------
// �R���X�g���N�^
//---------------------------------------------
KeyManager::KeyManager()
    : currentState()
    , prevState()
    , allKeyReleaseCount()
    , allButtonReleaseCount()
{
    // �����Ȃ�
}

//---------------------------------------------
// �f�X�g���N�^
//---------------------------------------------
KeyManager::~KeyManager()
{
    // �����Ȃ�
}

//---------------------------------------------
// �X�V����
//---------------------------------------------
void KeyManager::Update()
{
    for (int i = 0; i < 256; ++i)
    {
        prevState[i] = currentState[i]; // prev���X�V
    }

    GetHitKeyStateAll(currentState);  // current���X�V

    // �����L�[��������Ă�����J�E���g���Z�b�g
    for (int i = 0; i < 256; ++i)
    {
        if (currentState[i])
        {
            allKeyReleaseCount = 0;
            return;
        }
    }

    ++allKeyReleaseCount;

    // �Q�[���p�b�h��ڑ����Ă��Ȃ��ꍇ�͏������Ȃ�
    if (padNum == -1)
    {
        return;
    }

    // �Q�[���p�b�h�̐�������������
    for (int i = 0; i < padNum; ++i)
    {
        GetJoypadXInputState(i + 1, &input[i]);

        // �O�t���[���̓��͏�Ԃ��X�V
        UpdatePrevButton(i);
        // �g���K�[
        CheckTrigger(i);
        // �X�e�B�b�N���͏���
        CheckStick(i);
        // �X�e�B�b�N�|������
        CheckStickTilt(i);
        // �{�^�����͏���
        CheckButton(i);

        ++allButtonReleaseCount[i];

    }


}

//---------------------------------------------
// ��������L�[�������ꂽ��
//---------------------------------------------
bool KeyManager::CheckPressed(int keyCode) const
{
    if (currentState[keyCode] == 0)
    {
        return false;   // ���t���[���ŉ�����Ă��Ȃ�
    }
    return true;    // ���t���[���ŉ�����Ă���
}

//---------------------------------------------
// ��������̃L�[���������u�Ԃ�
//---------------------------------------------
bool KeyManager::CheckJustPressed(int keyCode) const
{
    if (prevState[keyCode] == 1)
    {
        return false;   // �O�t���[���ŉ�����Ă���
    }
    if (currentState[keyCode] == 0)
    {
        return false;   // ���t���[���ŉ�����Ă��Ȃ�
    }

    return true;    // ���t���[���ŏ��߂ĉ����ꂽ
}

//---------------------------------------------
// ��������̃L�[�𗣂�����
//---------------------------------------------
bool KeyManager::CheckRelease(int keyCode) const
{
    if (prevState[keyCode] == 0)
    {
        return false;   // �O�t���[���ŉ�����Ă��Ȃ�
    }
    if (currentState[keyCode] == 1)
    {
        return false;   // ���t���[���ŉ�����Ă���
    }

    return true;    // ���t���[���ŃL�[�͗����ꂽ
}

//---------------------------------------------
// �L�[�𗣂��Ă��鎞�Ԃ��擾
//---------------------------------------------
int KeyManager::GetKeyReleaseCount() const
{
    return allKeyReleaseCount;
}

/// <summary>
/// �p�b�h�̑������擾
/// </summary>
void KeyManager::CheckSetPad()
{
    // �p�b�h���ڑ�����Ă���ꍇ
    if (GetJoypadNum() > 0)
    {
        padNum = GetJoypadNum();
    }
    else
    {
        padNum = -1;
    }
}

/// <summary>
/// �{�^���̏�Ԃ��擾
/// </summary>
/// <param name="padNumber"></param>
/// <param name="keyCode"></param>
/// <returns></returns>
const int KeyManager::GetButton(const int padNumber, const int keyCode)
{
    return button[padNumber][keyCode];
}

/// <summary>
/// �g���K�[�̏�Ԃ��擾
/// </summary>
/// <param name="padNumber"></param>
/// <param name="keyCode"></param>
/// <returns></returns>
const int KeyManager::GetTrigger(const int padNumber, const int keyCode)
{
    return trigger[padNumber][keyCode];
}

/// <summary>
/// �X�e�B�b�N�̏�Ԃ��擾
/// </summary>
/// <param name="padNumber"></param>
/// <param name="keyCode"></param>
/// <returns></returns>
const int KeyManager::GetStick(const int padNumber, const int keyCode)
{
    return stick[padNumber][keyCode];
}

/// <summary>
/// �E�X�e�B�b�N�̓��͏�Ԃ�Ԃ�
/// </summary>
/// <param name="padNumber"></param>
/// <returns></returns>
const VECTOR KeyManager::GetRightStickInput(const int padNumber)
{
    float x;
    float y;

    x = (float)input->ThumbRX / Pad::STICK_MAX_VALUE;
    y = (float)input->ThumbRY / Pad::STICK_MAX_VALUE;

    VECTOR inputDir = VGet(x, 0.0f, y);

    return inputDir;
}

/// <summary>
/// ���X�e�B�b�N�̓��͏�Ԃ�Ԃ�
/// </summary>
/// <param name="padNumber"></param>
/// <returns></returns>
const VECTOR KeyManager::GetLeftStickInput(const int padNumber)
{
    float x;
    float y;

    x = (float)input->ThumbLX / Pad::STICK_MAX_VALUE;
    y = (float)input->ThumbLY / Pad::STICK_MAX_VALUE;

    VECTOR inputVec = VGet(x, 0.0f, y);
   
    return inputVec;
}

/// <summary>
/// �X�e�B�b�N���X���Ă��邩
/// </summary>
/// <param name="padNumber"></param>
/// <param name="keyCode"></param>
/// <param name="leftAndDownIsTrue"></param>
/// <returns></returns>
const int KeyManager::GetStickCheck(const int padNumber, const int keyCode, const bool leftAndDownIsTrue)
{
    if (leftAndDownIsTrue)
    {
        return stickCheck[padNumber][keyCode - 2];
    }
    else
    {
        return stickCheck[padNumber][keyCode - 2 + 4];
    }

}

const bool KeyManager::IsCheckEnd()
{
    return
    {
        (button[0][XINPUT_BUTTON_START] > 1 && button[0][XINPUT_BUTTON_BACK] > 1) ||
        (button[1][XINPUT_BUTTON_START] > 1 && button[1][XINPUT_BUTTON_BACK] > 1) ||
        (button[2][XINPUT_BUTTON_START] > 1 && button[2][XINPUT_BUTTON_BACK] > 1) ||
        (button[3][XINPUT_BUTTON_START] > 1 && button[3][XINPUT_BUTTON_BACK] > 1)
    };
}

/// <summary>
/// ��������{�^�����������u�Ԃ�
/// </summary>
/// <param name="padNumber"></param>
/// <param name="keyCode"></param>
/// <returns></returns>
const bool KeyManager::IsCheckButtonJustPressed(const int padNumber, const int keyCode)
{
    if (prevButton[padNumber][keyCode] > 0)
    {
        return false;       // �O�t���[���ŉ�����Ă���
    }
    if (button[padNumber][keyCode] == 0)
    {
        return false;       // ���t���[���ŉ�����Ă��Ȃ�
    }

    return true;            // ���t���[���ŏ��߂ĉ����ꂽ

}

/// <summary>
/// �{�^���������ꂽ��
/// </summary>
/// <param name="padNumber"></param>
/// <param name="keyCode"></param>
/// <returns></returns>
const bool KeyManager::IsCheckButtonRelease(const int padNumber, const int keyCode)
{
    if (prevButton[padNumber][keyCode] == 0)
    {
        return false;   // �O�t���[���ŉ�����Ă��Ȃ�
    }
    if (button[padNumber][keyCode] > 0)
    {
        return false;   // ���t���[���ŉ�����Ă���
    }

    return true;    // ���t���[���Ń{�^���������ꂽ
}


/// <summary>
/// �ڑ�����Ă���Q�[���p�b�h�̑�����Ԃ�
/// </summary>
/// <returns></returns>
const char KeyManager::GetpPadNum()
{
    return padNum;
}

/// <summary>
/// �O�t���[���̓��͏�Ԃ��X�V
/// </summary>
void KeyManager::UpdatePrevButton(int padNumber)
{
    for (int i = 0; i < 16; ++i)
    {
        prevButton[padNumber][i] = button[padNumber][i];
    }
}

/// <summary>
/// �S�{�^���̓��͏���
/// </summary>
/// <param name="padNumber"></param>
void KeyManager::CheckButton(int padNumber)
{
    for (int i = 0; i < 16; ++i)
    {
        // ������Ă��Ȃ�������
        if (input[padNumber].Buttons[i] == 0)
        {
            // ������
            if (button[padNumber][i] < 0)
            {
                button[padNumber][i] = 0;
            }
            // �����ꂽ�u��
            else if (button[padNumber][i] > 0)
            {
                button[padNumber][i] = -1;
            }
        }
        // i�Ԃ̃L�[�R�[�h�ɑΉ�����{�^����������Ă�����
        else if (input[padNumber].Buttons[i] == 1)
        {
            button[padNumber][i]++;
            // ��������{�^����������Ă�����J�E���g���Z�b�g
            allButtonReleaseCount[i] = 0;
            return;
        }

    }
}

/// <summary>
/// �g���K�[�̓��͏���
/// </summary>
/// <param name="padNumber"></param>
void KeyManager::CheckTrigger(int padNumber)
{
    trigger[padNumber][Pad::LEFT_TRIGGER] = input[padNumber].LeftTrigger;
    trigger[padNumber][Pad::RIGHT_TRIGGER] = input[padNumber].RightTrigger;
}

/// <summary>
/// �X�e�B�b�N�̓��͏���
/// </summary>
/// <param name="padNumber"></param>
void KeyManager::CheckStick(int padNumber)
{
    /// �X�e�B�b�N�̃f�b�h�]�[�����l���������͐��l���擾�i�f�b�h�]�[���͎󂯕t���Ȃ��l

    // ���X�e�B�b�N���E
    if (input[padNumber].ThumbLX > stickLX_DeadZoneMAX || input[padNumber].ThumbLX < stickLX_DeadZoneMIN)
    {
        stick[padNumber][Pad::LEFT_STICK_X] = input[padNumber].ThumbLX;
    }
    else
    {
        if (stick[padNumber][Pad::LEFT_STICK_X] != 0)
        {
            stick[padNumber][Pad::LEFT_STICK_X] = 0;
        }
    }

    // ���X�e�B�b�N�㉺
    if (input[padNumber].ThumbLY > stickLY_DeadZoneMAX || input[padNumber].ThumbLY < stickLY_DeadZoneMIN)
    {
        stick[padNumber][Pad::LEFT_STICK_Y] = input[padNumber].ThumbLY;
    }
    else
    {
        if (stick[padNumber][Pad::LEFT_STICK_Y] != 0)
        {
            stick[padNumber][Pad::LEFT_STICK_Y] = 0;
        }
    }

    // �E�X�e�B�b�N���E
    if (input[padNumber].ThumbRX > stickRX_DeadZoneMAX || input[padNumber].ThumbRX < stickRX_DeadZoneMIN)
    {
        stick[padNumber][Pad::RIGHT_STICK_X] = input[padNumber].ThumbRX;
    }
    else
    {
        if (stick[padNumber][Pad::RIGHT_STICK_X] != 0)
        {
            stick[padNumber][Pad::RIGHT_STICK_X] = 0;
        }

    }

    // �E�X�e�B�b�N�㉺
    if (input[padNumber].ThumbRY > stickRY_DeadZoneMAX || input[padNumber].ThumbRY < stickRY_DeadZoneMIN)
    {
        stick[padNumber][Pad::RIGHT_STICK_Y] = input[padNumber].ThumbRY;
    }
    else
    {
        if (stick[padNumber][Pad::RIGHT_STICK_Y] != 0)
        {
            stick[padNumber][Pad::RIGHT_STICK_Y] = 0;
        }
    }
}

/// <summary>
/// �X�e�B�b�N�����|������
/// </summary>
/// <param name="padNumber"></param>
void KeyManager::CheckStickTilt(int padNumber)
{
    // ���X�e�B�b�N���E�ɉ����|���Ă�����
    if (input[padNumber].ThumbLX == Pad::STICK_MAX_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_RIGHT)]++;
    }
    // ���X�e�B�b�N�����ɉ����|���Ă�����
    else if (input[padNumber].ThumbLX == Pad::STICK_MIN_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_LEFT)]++;
    }
    // ���X�e�B�b�N�������|����Ă��Ȃ�������
    else
    {
        if (stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_RIGHT)] < 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_RIGHT)] = 0;
        }
        else if (stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_RIGHT)] > 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_RIGHT)] = -1;
        }


        if (stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_LEFT)] < 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_LEFT)] = 0;
        }
        else if (stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_LEFT)] > 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_LEFT)] = -1;
        }
    }


    // ���X�e�B�b�N����ɉ����|���Ă�����
    if (input[padNumber].ThumbLY == Pad::STICK_MAX_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_UP)]++;
    }
    // ���X�e�B�b�N�����ɉ����|���Ă�����
    else if (input[padNumber].ThumbLY == Pad::STICK_MIN_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_DOWN)]++;
    }
    // ���X�e�B�b�N�������|����Ă��Ȃ�������
    else
    {
        if (stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_UP)] < 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_UP)] = 0;
        }
        else if (stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_UP)] > 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_UP)] = -1;
        }


        if (stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_DOWN)] < 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_DOWN)] = 0;
        }
        else if (stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_DOWN)] > 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_DOWN)] = -1;
        }
    }


    // �E�X�e�B�b�N���E�ɉ����|���Ă�����
    if (input[padNumber].ThumbRX == Pad::STICK_MAX_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_RIGHT)]++;
    }
    // �E�X�e�B�b�N�����ɉ����|���Ă�����
    else if (input[padNumber].ThumbRX == Pad::STICK_MIN_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_LEFT)]++;
    }
    // �E�X�e�B�b�N�������|����Ă��Ȃ�������
    else
    {
        if (stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_RIGHT)] < 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_RIGHT)] = 0;
        }
        else if (stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_RIGHT)] > 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_RIGHT)] = -1;
        }


        if (stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_LEFT)] < 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_LEFT)] = 0;
        }
        else if (stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_LEFT)] > 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_LEFT)] = -1;
        }
    }


    // �E�X�e�B�b�N����ɉ����|���Ă�����
    if (input[padNumber].ThumbRY == Pad::STICK_MAX_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_UP)]++;
    }
    // �E�X�e�B�b�N�����ɉ����|���Ă�����
    else if (input[padNumber].ThumbRY == Pad::STICK_MIN_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_DOWN)]++;
    }
    // �E�X�e�B�b�N�������|����Ă��Ȃ�������
    else
    {
        if (stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_UP)] < 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_UP)] = 0;
        }
        else if (stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_UP)] > 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_UP)] = -1;
        }


        if (stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_DOWN)] < 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_DOWN)] = 0;
        }
        else if (stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_DOWN)] > 0)
        {
            stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_DOWN)] = -1;
        }
    }
}
