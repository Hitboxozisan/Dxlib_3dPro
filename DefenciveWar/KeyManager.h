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
/// 操作関係管理クラス
/// シングルトン
/// </summary>
class KeyManager final
{
public:
    KeyManager();                        // コンストラクタ
    ~KeyManager();                       // デストラクタ

    void Update();

    bool CheckPressed(int keyCode) const;     // キーが押されているか
    bool CheckJustPressed(int keyCode) const; // キーが押された瞬間か
    bool CheckRelease(int keyCode) const;     // キーが離されたか

    int  GetKeyReleaseCount() const;          // 連続キー入力がないカウントを返す


    void CheckSetPad();                         // パッドの総数を取得

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
    //bool CheckButtonPressed(int keyCode) const; // ボタンが押されているか
    //bool CheckAnalogStick();
private:
    // キーボード
    char currentState[256];          // 現在のキー押下状態
    char prevState[256];             // 前フレームのキー押下状態
    int  allKeyReleaseCount;         // 連続キー入力がないカウント

    // スティック
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

    // ゲームパッドボタン
    enum class PadButton
    {
        INPUT_5 = 8,
        input_6 = 9
    };

    // ゲームパッドのスティックのデッドゾーン数値を保存
    static short stickLX_DeadZoneMAX;
    static short stickLX_DeadZoneMIN;
    static short stickLY_DeadZoneMAX;
    static short stickLY_DeadZoneMIN;
    static short stickRX_DeadZoneMAX;
    static short stickRX_DeadZoneMIN;
    static short stickRY_DeadZoneMAX;
    static short stickRY_DeadZoneMIN;

    // コントローラー
    int pad[4];                      // ゲームパッド
    int padNum;                      // ゲームパッドの総数
    int button[4][16];               // ゲームパッドの入力状態
    int prevButton[4][16];           // 前フレームのボタン入力状態
    int trigger[4][2];               // トリガーの入力状態
    int stick[4][6];                 // スティックの入力状態
    int stickCheck[4][8];
    XINPUT_STATE input[4];

    int allButtonReleaseCount[4];    // 連続ボタン入力がないカウント

    void UpdatePrevButton(int padNumber);         // 前フレームの入力状態を更新
    void CheckButton(int padNumber);              // 全ボタンの入力処理
    void CheckTrigger(int padNumber);             // トリガーの入力処理
    void CheckStick(int padNumber);               // スティックの入力処理
    void CheckStickTilt(int padNumber);           // スティックの押し倒し処理

    int analogInputX;
    int analogInputY;
};

