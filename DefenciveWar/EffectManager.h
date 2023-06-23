#pragma once

#include "EffectTypeData.h"

/// <summary>
/// エフェクト管理・再生クラス
/// シングルトン
/// </summary>
class EffectManager final
{
public:
	EffectManager();
	~EffectManager();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update(VECTOR pos);
	void Draw();

	void SetPlayEffect(const EffectType et, const VECTOR pos, bool isLoop);
	void StopPlayEffect(const EffectType et);

private:

	class EfkEffect* effect;

	//// エフェクトのリソース
	//std::map<EffectType, int> effectHandle;
	//// エフェクト本体
	//std::map<EffectType, int> effect;
	
};

