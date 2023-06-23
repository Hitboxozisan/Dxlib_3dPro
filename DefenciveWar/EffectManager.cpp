#include "common.h"

#include "EffectManager.h"
#include "EfkEffect.h"

/// <summary>
/// コンストラクタ
/// </summary>
EffectManager::EffectManager()
{
	effect = new EfkEffect();
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
EffectManager::~EffectManager()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void EffectManager::Initialize()
{
	effect->Initialize();	
}

/// <summary>
/// 終了処理
/// </summary>
void EffectManager::Finalize()
{
	effect->Finalize();
}

/// <summary>
/// 活性化処理
/// </summary>
/// <param name="inPosition"></param>
void EffectManager::Activate(VECTOR inPosition)
{
	
}

/// <summary>
/// 非活性化処理
/// </summary>
void EffectManager::Deactivate()
{
	
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="inPostion"></param>
/// <param name="inEnemyPosition"></param>
void EffectManager::Update(VECTOR pos)
{
	effect->Update();
	effect->UpdateLoop(pos);
	// Effekseerにより再生中のエフェクトを更新する
	UpdateEffekseer3D();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="inPosition"></param>
void EffectManager::Draw()
{
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}

void EffectManager::SetPlayEffect(const EffectType et, const VECTOR pos, bool isLoop)
{
	effect->SetPlayEffect(et, pos, isLoop);

}

void EffectManager::StopPlayEffect(const EffectType et)
{
	effect->StopPlayEffect(et);
}

