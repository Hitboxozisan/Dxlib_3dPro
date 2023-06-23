#include "common.h"
#include "DeltaTime.h"
#include "KeyManager.h"
#include "Singleton.h"

/// <summary>
/// コンストラクタ
/// </summary>
DeltaTime::DeltaTime()
    : key(Singleton<KeyManager>::GetInstance())
    , currentCount(0.0f)
    , prevCount(0.0f)
    , deltaTime(0.0f)
    , isSlow(false)
    , isStop(false)
{
    // 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
DeltaTime::~DeltaTime()
{
    // 処理なし
}

/// <summary>
/// deltaTimeの取得
/// </summary>
void DeltaTime::InstrumentationDeltaTime()
{
    if (key.CheckJustPressed(KEY_INPUT_7))
    {
        isStop = !isStop;
    }

    if (isStop)
    {
        deltaTime = 0.0f;
        return;
    }

    currentCount = GetNowCount();
    deltaTime = (currentCount - prevCount) / 1000.0f;
    prevCount = currentCount;
}

/// <summary>
/// ゲーム開始時のタイムを取得
/// </summary>
void DeltaTime::SetCount()
{
    currentCount = prevCount = GetNowCount();
}

const bool DeltaTime::IsStop()
{
    return isStop;
}
