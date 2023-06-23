#include "SupportJson.h"
#include "common.h"
#include "Player.h"
#include "ModelManager.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "Camera.h"
#include "EffectManager.h"
#include "EffectTypeData.h"
#include "Timer.h"
#include "DeltaTime.h"
#include "BulletManager.h"

#include "BossEnemy.h"

// VECTOR�̌v�Z�Ɏg�p
using namespace Math3d;

Player::Player(CollisionTag tag)
	:modelMgr(Singleton<ModelManager>::GetInstance())
	,effectMgr(Singleton<EffectManager>::GetInstance())
	,key(Singleton<KeyManager>::GetInstance())
	,camera(Singleton<Camera>::GetInstance())
	,bulletMgr(Singleton<BulletManager>::GetInstance())
	,json(Singleton<SupportJson>::GetInstance())
	,shotInterval(new Timer(SHOT_INTERVAL))
	,Mover(tag)
{
	param.collision->data.radius = json.GetFloat(JsonDataType::Player, "Radius");

	// ���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(modelMgr.GetModelHandle(ModelType::Player));
	// ���f���̃T�C�Y�ݒ�
	MV1SetScale(modelHandle, VGet(1.0f, 1.0f, 1.0f));
}

Player::~Player()
{ 
	// �����Ȃ�
}

void Player::Initialize()
{
	param.pos = json.GetVector(JsonDataType::Player, "Position");
	param.nextPos = param.pos;
	param.prevPos = param.pos;
	param.dir = json.GetVector(JsonDataType::Player, "Direction");
	hp = json.GetInt(JsonDataType::Player, "Hitpoint");
	exist = true;
}

void Player::Update()
{
	// �̗͂��s�����玀�S����
	if (hp <= 0.0f)
	{
		hp = 0;
		exist = false;
	}

	// �e���ˏ���
	Shot();

	// �V�[���h����
	CreateShield();

	// �ړ�����
	Move();

	// �ʒu�C��
	ModifyingPosition();
	// ���ۂɃ��f�����ړ�
	MoveFinish();
	// ���f���̌���������
	MV1SetRotationYUseDir(modelHandle, param.dir, 0.0f);

}

void Player::Draw()
{
	// ���f���̕`��
	MV1DrawModel(modelHandle);
}

/// <summary>
/// �e�I�u�W�F�N�g�ɐG�ꂽ�ۂ̏���
/// </summary>
/// <param name="tag"></param>
void Player::HitObject(CollisionTag tag)
{
	if (tag == CollisionTag::Enemy)
	{
		// �G�t�F�N�g�̍Đ�
		// �T�E���h�̍Đ�

	}
}

const int Player::GetMaxHitpoint() const
{
	return json.GetInt(JsonDataType::Player, "Hitpoint");
}


/// <summary>
/// �ړ�����
/// ���łɃv���C���[�̕�������������Ƃ�
/// </summary>
void Player::Move()
{

	// ���̓x�N�g��
	VECTOR inputL = ZERO_VECTOR;
	VECTOR inputR = ZERO_VECTOR;

	// �O�����x�N�g�����o��
	VECTOR forward = VSub(param.pos, camera.GetPos());
	// �㉺�̊T�O�͍l�����Ȃ�
	forward.y = 0;
	// ���K��
	forward = VNorm(forward);

	// �O�ς��牡�������o��
	VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), forward);
	// ���K��
	right = VNorm(right);

	VECTOR inputScaleL = key.GetLeftStickInput(Pad::Player1);
	VECTOR inputScaleR = key.GetRightStickInput(Pad::Player1);

	inputL = VAdd(inputL, VScale(forward, inputScaleL.z));
	inputL = VAdd(inputL, VScale(right, inputScaleL.x));

	param.nextPos = VAdd(param.nextPos, VScale(inputL, SPEED));


	// �������ω����Ȃ������͂��̕���������
	if (inputScaleR != ZERO_VECTOR)
	{
		inputR = VAdd(inputR, VScale(forward, inputScaleR.z));
		inputR = VAdd(inputR, VScale(right, inputScaleR.x));

		param.dir = VAdd(param.dir, inputR);
		// ���K��
		param.dir = VNorm(param.dir);
	}

}

/// <summary>
/// �e�̔���
/// </summary>
void Player::Shot()
{
	// �C���^�[�o���^�C�}�[�X�V
	shotInterval->Update(deltaTime.GetDeltaTime());

	if (key.GetButton(Pad::Player1, XINPUT_BUTTON_RIGHT_SHOULDER) &&
		shotInterval->IsTimeout())
	{
		// �e�𔭎˂���
		bulletMgr.CreateBullet(param.pos, param.dir, BULLET_SPEED, ModelType::Bullet);
		// �^�C�}�[�����Z�b�g
		shotInterval->Reset();
	}
}

/// <summary>
/// �V�[���h�쐬
/// </summary>
void Player::CreateShield()
{
	if (key.GetButton(Pad::Player1, XINPUT_BUTTON_LEFT_SHOULDER))
	{
		effectMgr.SetPlayEffect(EffectType::Shield, param.pos, true);
	}
	else
	{
		effectMgr.StopPlayEffect(EffectType::Shield);
	}
}
