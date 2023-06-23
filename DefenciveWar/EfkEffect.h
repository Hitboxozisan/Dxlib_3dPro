#pragma once

#include "EffectTypeData.h"

class EfkEffect
{
public:
	EfkEffect();
	~EfkEffect();

	void Initialize();
	void Finalize();
	void Update();
	void UpdateLoop(VECTOR pos);

	void SetPlayEffect(const EffectType et, const VECTOR pos, bool isLoop);
	void StopPlayEffect(const EffectType et);
private:
	struct Param
	{
		int handle = 0;
		bool isLoop = false;
	};

	// エフェクトのリソース
	std::map<EffectType, int> effectHandle;
	// エフェクト本体
	std::map<EffectType, Param> effect;
};

