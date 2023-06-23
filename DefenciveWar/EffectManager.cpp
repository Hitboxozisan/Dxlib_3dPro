#include "common.h"

#include "EffectManager.h"
#include "EfkEffect.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectManager::EffectManager()
{
	effect = new EfkEffect();
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectManager::~EffectManager()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void EffectManager::Initialize()
{
	effect->Initialize();	
}

/// <summary>
/// �I������
/// </summary>
void EffectManager::Finalize()
{
	effect->Finalize();
}

/// <summary>
/// ����������
/// </summary>
/// <param name="inPosition"></param>
void EffectManager::Activate(VECTOR inPosition)
{
	
}

/// <summary>
/// �񊈐�������
/// </summary>
void EffectManager::Deactivate()
{
	
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="inPostion"></param>
/// <param name="inEnemyPosition"></param>
void EffectManager::Update(VECTOR pos)
{
	effect->Update();
	effect->UpdateLoop(pos);
	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����
	UpdateEffekseer3D();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="inPosition"></param>
void EffectManager::Draw()
{
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
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

