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

// VECTORの計算に使用
using namespace Math3d;

//---------------------------------------------
// コンストラクタ
//---------------------------------------------
KeyManager::KeyManager()
    : currentState()
    , prevState()
    , allKeyReleaseCount()
    , allButtonReleaseCount()
{
    // 処理なし
}

//---------------------------------------------
// デストラクタ
//---------------------------------------------
KeyManager::~KeyManager()
{
    // 処理なし
}

//---------------------------------------------
// 更新処理
//---------------------------------------------
void KeyManager::Update()
{
    for (int i = 0; i < 256; ++i)
    {
        prevState[i] = currentState[i]; // prevを更新
    }

    GetHitKeyStateAll(currentState);  // currentを更新

    // 何かキーが押されていたらカウントリセット
    for (int i = 0; i < 256; ++i)
    {
        if (currentState[i])
        {
            allKeyReleaseCount = 0;
            return;
        }
    }

    ++allKeyReleaseCount;

    // ゲームパッドを接続していない場合は処理しない
    if (padNum == -1)
    {
        return;
    }

    // ゲームパッドの数だけ処理する
    for (int i = 0; i < padNum; ++i)
    {
        GetJoypadXInputState(i + 1, &input[i]);

        // 前フレームの入力状態を更新
        UpdatePrevButton(i);
        // トリガー
        CheckTrigger(i);
        // スティック入力処理
        CheckStick(i);
        // スティック倒し処理
        CheckStickTilt(i);
        // ボタン入力処理
        CheckButton(i);

        ++allButtonReleaseCount[i];

    }


}

//---------------------------------------------
// 何かしらキーが押されたら
//---------------------------------------------
bool KeyManager::CheckPressed(int keyCode) const
{
    if (currentState[keyCode] == 0)
    {
        return false;   // 現フレームで押されていない
    }
    return true;    // 現フレームで押されている
}

//---------------------------------------------
// 何かしらのキーを押した瞬間か
//---------------------------------------------
bool KeyManager::CheckJustPressed(int keyCode) const
{
    if (prevState[keyCode] == 1)
    {
        return false;   // 前フレームで押されている
    }
    if (currentState[keyCode] == 0)
    {
        return false;   // 現フレームで押されていない
    }

    return true;    // 現フレームで初めて押された
}

//---------------------------------------------
// 何かしらのキーを離したか
//---------------------------------------------
bool KeyManager::CheckRelease(int keyCode) const
{
    if (prevState[keyCode] == 0)
    {
        return false;   // 前フレームで押されていない
    }
    if (currentState[keyCode] == 1)
    {
        return false;   // 現フレームで押されている
    }

    return true;    // 現フレームでキーは離された
}

//---------------------------------------------
// キーを離している時間を取得
//---------------------------------------------
int KeyManager::GetKeyReleaseCount() const
{
    return allKeyReleaseCount;
}

/// <summary>
/// パッドの総数を取得
/// </summary>
void KeyManager::CheckSetPad()
{
    // パッドが接続されている場合
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
/// ボタンの状態を取得
/// </summary>
/// <param name="padNumber"></param>
/// <param name="keyCode"></param>
/// <returns></returns>
const int KeyManager::GetButton(const int padNumber, const int keyCode)
{
    return button[padNumber][keyCode];
}

/// <summary>
/// トリガーの状態を取得
/// </summary>
/// <param name="padNumber"></param>
/// <param name="keyCode"></param>
/// <returns></returns>
const int KeyManager::GetTrigger(const int padNumber, const int keyCode)
{
    return trigger[padNumber][keyCode];
}

/// <summary>
/// スティックの状態を取得
/// </summary>
/// <param name="padNumber"></param>
/// <param name="keyCode"></param>
/// <returns></returns>
const int KeyManager::GetStick(const int padNumber, const int keyCode)
{
    return stick[padNumber][keyCode];
}

/// <summary>
/// 右スティックの入力状態を返す
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
/// 左スティックの入力状態を返す
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
/// スティックが傾いているか
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
/// 何かしらボタンを押した瞬間か
/// </summary>
/// <param name="padNumber"></param>
/// <param name="keyCode"></param>
/// <returns></returns>
const bool KeyManager::IsCheckButtonJustPressed(const int padNumber, const int keyCode)
{
    if (prevButton[padNumber][keyCode] > 0)
    {
        return false;       // 前フレームで押されている
    }
    if (button[padNumber][keyCode] == 0)
    {
        return false;       // 現フレームで押されていない
    }

    return true;            // 現フレームで初めて押された

}

/// <summary>
/// ボタンが離されたか
/// </summary>
/// <param name="padNumber"></param>
/// <param name="keyCode"></param>
/// <returns></returns>
const bool KeyManager::IsCheckButtonRelease(const int padNumber, const int keyCode)
{
    if (prevButton[padNumber][keyCode] == 0)
    {
        return false;   // 前フレームで押されていない
    }
    if (button[padNumber][keyCode] > 0)
    {
        return false;   // 現フレームで押されている
    }

    return true;    // 現フレームでボタンが離された
}


/// <summary>
/// 接続されているゲームパッドの総数を返す
/// </summary>
/// <returns></returns>
const char KeyManager::GetpPadNum()
{
    return padNum;
}

/// <summary>
/// 前フレームの入力状態を更新
/// </summary>
void KeyManager::UpdatePrevButton(int padNumber)
{
    for (int i = 0; i < 16; ++i)
    {
        prevButton[padNumber][i] = button[padNumber][i];
    }
}

/// <summary>
/// 全ボタンの入力処理
/// </summary>
/// <param name="padNumber"></param>
void KeyManager::CheckButton(int padNumber)
{
    for (int i = 0; i < 16; ++i)
    {
        // 押されていなかったら
        if (input[padNumber].Buttons[i] == 0)
        {
            // 離した
            if (button[padNumber][i] < 0)
            {
                button[padNumber][i] = 0;
            }
            // 離された瞬間
            else if (button[padNumber][i] > 0)
            {
                button[padNumber][i] = -1;
            }
        }
        // i番のキーコードに対応するボタンが押されていたら
        else if (input[padNumber].Buttons[i] == 1)
        {
            button[padNumber][i]++;
            // 何かしらボタンが押されていたらカウントリセット
            allButtonReleaseCount[i] = 0;
            return;
        }

    }
}

/// <summary>
/// トリガーの入力処理
/// </summary>
/// <param name="padNumber"></param>
void KeyManager::CheckTrigger(int padNumber)
{
    trigger[padNumber][Pad::LEFT_TRIGGER] = input[padNumber].LeftTrigger;
    trigger[padNumber][Pad::RIGHT_TRIGGER] = input[padNumber].RightTrigger;
}

/// <summary>
/// スティックの入力処理
/// </summary>
/// <param name="padNumber"></param>
void KeyManager::CheckStick(int padNumber)
{
    /// スティックのデッドゾーンを考慮した入力数値を取得（デッドゾーンは受け付けない値

    // 左スティック左右
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

    // 左スティック上下
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

    // 右スティック左右
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

    // 右スティック上下
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
/// スティック押し倒し処理
/// </summary>
/// <param name="padNumber"></param>
void KeyManager::CheckStickTilt(int padNumber)
{
    // 左スティックを右に押し倒していたら
    if (input[padNumber].ThumbLX == Pad::STICK_MAX_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_RIGHT)]++;
    }
    // 左スティックを左に押し倒していたら
    else if (input[padNumber].ThumbLX == Pad::STICK_MIN_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_LEFT)]++;
    }
    // 左スティックが押し倒されていなかったら
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


    // 左スティックを上に押し倒していたら
    if (input[padNumber].ThumbLY == Pad::STICK_MAX_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_UP)]++;
    }
    // 左スティックを下に押し倒していたら
    else if (input[padNumber].ThumbLY == Pad::STICK_MIN_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::LEFT_STICK_DOWN)]++;
    }
    // 左スティックが押し倒されていなかったら
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


    // 右スティックを右に押し倒していたら
    if (input[padNumber].ThumbRX == Pad::STICK_MAX_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_RIGHT)]++;
    }
    // 右スティックを左に押し倒していたら
    else if (input[padNumber].ThumbRX == Pad::STICK_MIN_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_LEFT)]++;
    }
    // 右スティックが押し倒されていなかったら
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


    // 右スティックを上に押し倒していたら
    if (input[padNumber].ThumbRY == Pad::STICK_MAX_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_UP)]++;
    }
    // 右スティックを下に押し倒していたら
    else if (input[padNumber].ThumbRY == Pad::STICK_MIN_VALUE)
    {
        stickCheck[padNumber][static_cast<int>(StickCheck::RIGHT_STICK_DOWN)]++;
    }
    // 右スティックが押し倒されていなかったら
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
