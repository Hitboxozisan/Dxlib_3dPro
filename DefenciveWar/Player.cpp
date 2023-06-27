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
#include "Shield.h"

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
	,invincibleTime(new Timer(INVINCIBLE_TIME))
	,shield(new Shield(CollisionTag::PlayerShield))
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
	delete shotInterval;
	delete shield;
}

/// <summary>
/// ����������
/// </summary>
void Player::Initialize()
{
	param.pos = json.GetVector(JsonDataType::Player, "Position");
	param.nextPos = param.pos;
	param.prevPos = param.pos;
	param.dir = json.GetVector(JsonDataType::Player, "Direction");
	hp = json.GetInt(JsonDataType::Player, "Hitpoint");
	exist = true;
}

/// <summary>
/// �X�V����
/// </summary>
void Player::Update()
{
	// �̗͂��s�����玀�S����
	if (hp <= 0.0f)
	{
		hp = 0;
		exist = false;
	}

	// �ڐG�����ꍇ
	if (isHit)
	{
		// ���G���
		invincibleTime->Update(deltaTime.GetDeltaTime());
		if (invincibleTime->IsTimeout())
		{
			isHit = false;
			invincibleTime->Reset();
		}
	}

	// �e���ˏ���
	Shot();

	// �V�[���h����
	CreateShield();
	shield->Update(param.pos);

	if (VSize(force) == 0)
	{
		// �ړ�����
		Move();
	}
	else
	{
		Sliding();
	}
	
	// �ʒu�C��
	ModifyingPosition();
	// ���ۂɃ��f�����ړ�
	MoveFinish();
	// ���f���̌���������
	MV1SetRotationYUseDir(modelHandle, param.dir, 0.0f);
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{
	DrawFormatString(1700.0f, 50.0f, GetColor(255, 255, 255), "PlayerX: %f", shield->GetTrunkpoint());

	// ���f���̕`��
	MV1DrawModel(modelHandle);
}

/// <summary>
/// �e�I�u�W�F�N�g�ɐG�ꂽ�ۂ̏���
/// </summary>
/// <param name="tag"></param>
void Player::HitObject(Collision* other)
{
	VECTOR sub;

	if (other->GetTag() == CollisionTag::Enemy && !isHit)
	{
		// �G�t�F�N�g�̍Đ�
		
		// �T�E���h�̍Đ�

		// �̗͂̌���
		hp -= DECREMENT_HP;

		// ���˕Ԃ�͂�ݒ�
		 // ���˕Ԃ������ݒ�
		sub = VSub(param.pos, other->GetPos());
		 // ���K��
		force = VNorm(sub);
		 // �͂̑傫����ݒ�
		force = VScale(force, BOUND_POWER);

		isHit = true;
	}
}

/// <summary>
/// �ړ�����
/// ���łɃv���C���[�̕�������������Ƃ�
/// </summary>
void Player::Move()
{
	float delta = deltaTime.GetDeltaTime();
	float speed = json.GetFloat(JsonDataType::Player, "Speed");

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

	param.nextPos = VAdd(param.nextPos, VScale(inputL, speed * delta));


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
	float speed = json.GetFloat(JsonDataType::Player, "BulletSpeed");

	// �C���^�[�o���^�C�}�[�X�V
	shotInterval->Update(deltaTime.GetDeltaTime());

	if (key.GetButton(Pad::Player1, XINPUT_BUTTON_RIGHT_SHOULDER) &&
		shotInterval->IsTimeout())
	{
		// �e�𔭎˂���
		bulletMgr.CreateBullet(param.pos, param.dir, speed, ModelType::Bullet);
		// �^�C�}�[�����Z�b�g
		shotInterval->Reset();
	}
}

/// <summary>
/// �V�[���h�쐬
/// </summary>
void Player::CreateShield()
{
	if (key.GetButton(Pad::Player1, XINPUT_BUTTON_LEFT_SHOULDER) &&
		!shield->IsBreak())
	{
		shield->Activate(param.pos);
	}
	else
	{
		shield->Deactivate();
	}
}

bool Player::Sliding()
{
	float delta = deltaTime.GetDeltaTime();
	VECTOR friction = force;
	friction = VNorm(friction);
	friction = VScale(friction, REBOUND_RESISTANCE);

	force = VAdd(force, friction * delta);
	param.nextPos = VAdd(param.nextPos, force);
	
	// �����͂� 0 �����������I������
	if (VSize(force) <= 0)
	{
		force = ZERO_VECTOR;
		return true;
	}

	return false;
}

const int Player::GetMaxHitpoint() const
{
	return json.GetInt(JsonDataType::Player, "Hitpoint");
}

