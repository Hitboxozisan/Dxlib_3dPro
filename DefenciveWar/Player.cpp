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
	// 処理なし
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
	// 体力が尽きたら死亡する
	if (hp <= 0.0f)
	{
		hp = 0;
		exist = false;
	}

	// 弾発射処理
	Shot();

	// シールド処理
	CreateShield();

	// 移動処理
	Move();

	// 位置修正
	ModifyingPosition();
	// 実際にモデルを移動
	MoveFinish();
	// モデルの向きを決定
	MV1SetRotationYUseDir(modelHandle, param.dir, 0.0f);

}

void Player::Draw()
{
	// モデルの描画
	MV1DrawModel(modelHandle);
}

/// <summary>
/// 各オブジェクトに触れた際の処理
/// </summary>
/// <param name="tag"></param>
void Player::HitObject(CollisionTag tag)
{
	if (tag == CollisionTag::Enemy)
	{
		// エフェクトの再生
		// サウンドの再生

	}
}

const int Player::GetMaxHitpoint() const
{
	return json.GetInt(JsonDataType::Player, "Hitpoint");
}


/// <summary>
/// 移動処理
/// ついでにプレイヤーの方向処理もやっとく
/// </summary>
void Player::Move()
{

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

	param.nextPos = VAdd(param.nextPos, VScale(inputL, SPEED));


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
	// インターバルタイマー更新
	shotInterval->Update(deltaTime.GetDeltaTime());

	if (key.GetButton(Pad::Player1, XINPUT_BUTTON_RIGHT_SHOULDER) &&
		shotInterval->IsTimeout())
	{
		// 弾を発射する
		bulletMgr.CreateBullet(param.pos, param.dir, BULLET_SPEED, ModelType::Bullet);
		// タイマーをリセット
		shotInterval->Reset();
	}
}

/// <summary>
/// シールド作成
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
