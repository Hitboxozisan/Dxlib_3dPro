#pragma once

namespace Pad
{
    const int Player1 = 0;
    const int Player2 = 1;

    const int LEFT_TRIGGER = 0;
    const int RIGHT_TRIGGER = 1;
    const int LEFT_STICK_X = 2;
    const int LEFT_STICK_Y = 3;
    const int RIGHT_STICK_X = 4;
    const int RIGHT_STICK_Y = 5;

    const int STICK_MAX_VALUE = 32767;
    const int STICK_MIN_VALUE = -32768;
}

/// <summary>
/// ����֌W�Ǘ��N���X
/// �V���O���g��
/// </summary>
class KeyManager final
{
public:
    KeyManager();                        // �R���X�g���N�^
    ~KeyManager();                       // �f�X�g���N�^

    void Update();

    bool CheckPressed(int keyCode) const;     // �L�[��������Ă��邩
    bool CheckJustPressed(int keyCode) const; // �L�[�������ꂽ�u�Ԃ�
    bool CheckRelease(int keyCode) const;     // �L�[�������ꂽ��

    int  GetKeyReleaseCount() const;          // �A���L�[���͂��Ȃ��J�E���g��Ԃ�


    void CheckSetPad();                         // �p�b�h�̑������擾

    const int GetButton(const int padNumber, const int keyCode);
    const int GetTrigger(const int padNumber, const int keyCode);
    const int GetStick(const int padNumber, const int keyCode);
    const VECTOR GetRightStickInput(const int padNumber);
    const VECTOR GetLeftStickInput(const int padNumber);
    const int GetStickCheck(const int padNumber, const int keyCode, const bool leftAndDownIsTrue);
    const bool IsCheckEnd();
    const bool IsCheckButtonJustPressed(const int padNumber, const int keyCode);
    const bool IsCheckButtonRelease(const int padNumber, const int keyCode);
    const char GetpPadNum();
    //bool CheckButtonPressed(int keyCode) const; // �{�^����������Ă��邩
    //bool CheckAnalogStick();
private:
    // �L�[�{�[�h
    char currentState[256];          // ���݂̃L�[�������
    char prevState[256];             // �O�t���[���̃L�[�������
    int  allKeyReleaseCount;         // �A���L�[���͂��Ȃ��J�E���g

    // �X�e�B�b�N
    enum class StickCheck
    {
        LEFT_STICK_LEFT,
        LEFT_STICK_DOWN,
        RIGHT_STICK_LEFT,
        RIGHT_STICK_DOWN,
        LEFT_STICK_RIGHT,
        LEFT_STICK_UP,
        RIGHT_STICK_RIGHT,
        RIGHT_STICK_UP
    };

    // �Q�[���p�b�h�{�^��
    enum class PadButton
    {
        INPUT_5 = 8,
        input_6 = 9
    };

    // �Q�[���p�b�h�̃X�e�B�b�N�̃f�b�h�]�[�����l��ۑ�
    static short stickLX_DeadZoneMAX;
    static short stickLX_DeadZoneMIN;
    static short stickLY_DeadZoneMAX;
    static short stickLY_DeadZoneMIN;
    static short stickRX_DeadZoneMAX;
    static short stickRX_DeadZoneMIN;
    static short stickRY_DeadZoneMAX;
    static short stickRY_DeadZoneMIN;

    // �R���g���[���[
    int pad[4];                      // �Q�[���p�b�h
    int padNum;                      // �Q�[���p�b�h�̑���
    int button[4][16];               // �Q�[���p�b�h�̓��͏��
    int prevButton[4][16];           // �O�t���[���̃{�^�����͏��
    int trigger[4][2];               // �g���K�[�̓��͏��
    int stick[4][6];                 // �X�e�B�b�N�̓��͏��
    int stickCheck[4][8];
    XINPUT_STATE input[4];

    int allButtonReleaseCount[4];    // �A���{�^�����͂��Ȃ��J�E���g

    void UpdatePrevButton(int padNumber);         // �O�t���[���̓��͏�Ԃ��X�V
    void CheckButton(int padNumber);              // �S�{�^���̓��͏���
    void CheckTrigger(int padNumber);             // �g���K�[�̓��͏���
    void CheckStick(int padNumber);               // �X�e�B�b�N�̓��͏���
    void CheckStickTilt(int padNumber);           // �X�e�B�b�N�̉����|������

    int analogInputX;
    int analogInputY;
};

