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

// VECTORの計算に使用
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

	// モデルの読み込み
	modelHandle = MV1DuplicateModel(modelMgr.GetModelHandle(ModelType::Player));
	// モデルのサイズ設定
	MV1SetScale(modelHandle, VGet(1.0f, 1.0f, 1.0f));
}

Player::~Player()
{ 
	delete shotInterval;
	delete invincibleTime;
	delete shield;
}

/// <summary>
/// 初期化処理
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
/// 更新処理
/// </summary>
void Player::Update()
{
	// 体力が尽きたら死亡する
	if (hp <= 0.0f)
	{
		hp = 0;
		exist = false;
	}

	// 地面をすり抜けないようにする
	if (param.nextPos.y <= 0)
	{
		param.nextPos.y = 0;
	}

	if (key.CheckPressed(KEY_INPUT_0))
	{
		param.nextPos.y += 1;
	}
	if (key.CheckPressed(KEY_INPUT_1))
	{
		param.nextPos.y -= 1;
	}

	// 接触した場合
	if (isHit)
	{
		// 無敵状態
		if (isInvincible)
		{
			noDrawFlame = !noDrawFlame;
			invincibleTime->Update(deltaTime.GetDeltaTime());
		}

		if (invincibleTime->IsTimeout())
		{
			isHit = false;
			isInvincible = false;
			noDrawFlame = false;
			invincibleTime->Reset();
		}
	}

	// 弾発射処理
	Shot();

	// シールド処理
	CreateShield();
	shield->Update(param.pos);

	// ダメージを受けた場合は移動を制限する
	if (VSize(force) == 0)
	{
		// 移動処理
		Move();
	}
	else
	{
		Sliding();
	}
	
	// 位置修正
	ModifyingPosition();
	// 実際にモデルを移動
	MoveFinish();
	// モデルの向きを決定
	MV1SetRotationYUseDir(modelHandle, param.dir, 0.0f);
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
	if (noDrawFlame)
	{
		return;
	}

	// モデルの描画
	MV1DrawModel(modelHandle);
}

/// <summary>
/// 各オブジェクトに触れた際の処理
/// </summary>
/// <param name="tag"></param>
void Player::HitObject(Collision* other)
{
	VECTOR sub;

	if (other->GetTag() == CollisionTag::Enemy && !isHit)
	{
		// エフェクトの再生
		
		// サウンドの再生

		// 体力の減少
		hp -= DECREMENT_HP;

		// 跳ね返る力を設定
		 // 跳ね返る向きを設定
		sub = VSub(param.pos, other->GetPos());
		 // 正規化
		force = VNorm(sub);
		 // 力の大きさを設定
		force = VScale(force, BOUND_POWER);

		isHit = true;
	}

	if (other->GetTag() == CollisionTag::EnemyBullet && !isHit)
	{

	}
}

/// <summary>
/// 移動処理
/// </summary>
void Player::Move()
{
	float delta = deltaTime.GetDeltaTime();
	float speed = json.GetFloat(JsonDataType::Player, "Speed");

	// 入力ベクトル
	VECTOR inputL = ZERO_VECTOR;
	VECTOR inputR = ZERO_VECTOR;

	// 前方向ベクトルを出す
	VECTOR forward = VSub(param.pos, camera.GetPos());
	// 上下の概念は考慮しない
	forward.y = 0;
	// 正規化
	forward = VNorm(forward);

	// 外積から横方向を出す
	VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), forward);
	// 正規化
	right = VNorm(right);

	VECTOR inputScaleL = key.GetLeftStickInput(Pad::Player1);
	VECTOR inputScaleR = key.GetRightStickInput(Pad::Player1);

	inputL = VAdd(inputL, VScale(forward, inputScaleL.z));
	inputL = VAdd(inputL, VScale(right, inputScaleL.x));

	param.nextPos = VAdd(param.nextPos, VScale(inputL, speed * delta));


	// 向きが変化しないうちはその方向を向く
	if (inputScaleR != ZERO_VECTOR)
	{
		inputR = VAdd(inputR, VScale(forward, inputScaleR.z));
		inputR = VAdd(inputR, VScale(right, inputScaleR.x));

		param.dir = VAdd(param.dir, inputR);
		// 正規化
		param.dir = VNorm(param.dir);
	}

}

/// <summary>
/// 弾の発射
/// </summary>
void Player::Shot()
{
	float speed = json.GetFloat(JsonDataType::Player, "BulletSpeed");

	// インターバルタイマー更新
	shotInterval->Update(deltaTime.GetDeltaTime());

	if (key.GetButton(Pad::Player1, XINPUT_BUTTON_RIGHT_SHOULDER) &&
		shotInterval->IsTimeout())
	{
		// 弾を発射する
		bulletMgr.CreateBullet(param.pos, param.dir, speed, ModelType::Bullet);
		// タイマーをリセット
		shotInterval->Reset();
	}
}

/// <summary>
/// シールド作成
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

	force = VAdd(force, VScale(friction, delta));
	param.nextPos = VAdd(param.nextPos, force);
	
	// 反発力が 0 を下回ったら終了する
	if (VSize(force) <= 0)
	{
		force = ZERO_VECTOR;
		isInvincible = true;
		shield->SetHit(false);
		return true;
	}

	return false;
}

const int Player::GetMaxHitpoint() const
{
	return json.GetInt(JsonDataType::Player, "Hitpoint");
}

