#include "common.h"
#include "EfkEffect.h"
#include "EffectData.h"

using namespace EffectData;

EfkEffect::EfkEffect()
{
	Initialize();
}

EfkEffect::~EfkEffect()
{
	// �����Ȃ�
}

void EfkEffect::Initialize()
{
	//�e�G�t�F�N�g������
	for (int i = 0; i < static_cast<int>(EffectType::EffectAmount); i++)
	{
		EffectType et = static_cast<EffectType>(i);
		// �p�X�̐ݒ�
		effectHandle[et] = LoadEffekseerEffect(EFFECT_PATH[et].c_str(), EFFECT_SIZE[et]);
		if (effectHandle[et] < 0)
		{
			printfDx("Error_Effect[%d]", i + 1);
		}
	}
}

void EfkEffect::Finalize()
{
	for (int i = 0; i < static_cast<int>(EffectType::EffectAmount); i++)
	{
		EffectType et = static_cast<EffectType>(i);
		// ���\�[�X�̍폜
		DeleteEffekseerEffect(effectHandle[et]);
	}
}

void EfkEffect::Update()
{
	for (int i = 0; i < static_cast<int>(EffectType::EffectAmount); i++)
	{

	}
}

void EfkEffect::UpdateLoop(VECTOR pos)
{
	for (int i = 0; i < static_cast<int>(EffectType::EffectAmount); i++)
	{
		EffectType et = static_cast<EffectType>(i);
		if (effect[et].isLoop)
		{
			if (IsEffekseer3DEffectPlaying(effect[et].handle))
			{
				effect[et].handle = PlayEffekseer3DEffect(effectHandle[et]);
			}
			SetPosPlayingEffekseer3DEffect(effect[et].handle, pos.x, pos.y, pos.z);
		}
	}
}

void EfkEffect::SetPlayEffect(const EffectType et, const VECTOR pos, bool isLoop)
{
	// �G�t�F�N�g���Đ����̏ꍇ�͖���
	if (IsEffekseer3DEffectPlaying(effect[et].handle))
	{
		effect[et].handle = PlayEffekseer3DEffect(effectHandle[et]);
		effect[et].isLoop = isLoop;
		SetPosPlayingEffekseer3DEffect(effect[et].handle, pos.x, pos.y, pos.z);
	}
}

void EfkEffect::StopPlayEffect(const EffectType et)
{
	StopEffekseer3DEffect(effect[et].handle);
}
