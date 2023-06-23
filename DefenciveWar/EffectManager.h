#pragma once

#include "EffectTypeData.h"

/// <summary>
/// �G�t�F�N�g�Ǘ��E�Đ��N���X
/// �V���O���g��
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

	//// �G�t�F�N�g�̃��\�[�X
	//std::map<EffectType, int> effectHandle;
	//// �G�t�F�N�g�{��
	//std::map<EffectType, int> effect;
	
};

