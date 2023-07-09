#include "SupportJson.h"
#include "BossEnemy.h"
#include "BossEnemyTimerData.h"
#include "Timer.h"
#include "Random.h"
#include "Singleton.h"
#include "DeltaTime.h"
#include "ModelManager.h"
#include "Player.h"
#include "EnemyBulletManager.h"
#include "BossMagnification.h"

#include "BehaviorManager.h"
#include "NodeBase.h"
#include "ActAssault.h"
#include "ActBulletNormal.h"
#include "ActBulletShotGun.h"
#include "ActStomp.h"

#include "KeyManager.h"

using namespace BossTimer;

BossEnemy::BossEnemy(CollisionTag tag, Player* p)
	:random(Singleton<Random>::GetInstance())
	,modelMgr(Singleton<ModelManager>::GetInstance())
	,bulletMgr(Singleton<EnemyBulletManager>::GetInstance())
	,json(Singleton<SupportJson>::GetInstance())
	,key(Singleton<KeyManager>::GetInstance())
	,aiMgr(new BehaviorManager())
	,magnification(new BossMagnification)
	,Mover(tag)
{
	player = p;

	int size = static_cast<int>(TimerType::TimerAmount);
	for (int i = 0; i < size; i++)
	{
		TimerType tk = static_cast<TimerType>(i);
		timer[tk] = new Timer(TIMER[tk]);
	}

	param.collision->data.radius = json.GetFloat(JsonDataType::BossEnemy, "Radius");

	modelHandle = MV1DuplicateModel(modelMgr.GetModelHandle(ModelType::Enemy));
	MV1SetScale(modelHandle, VGet(1.0f, 1.0f, 1.0f));
	// マテリアルの色を変更
	MV1SetMaterialEmiColor(modelHandle, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));

	// ビヘイビアツリー設定
	SetupBehavior();
}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::Initialize()
{
	param.pos = json.GetVector(JsonDataType::BossEnemy, "Position");
	param.prevPos = param.pos;
	param.nextPos = param.pos;

	//actNode = nullptr;
	isGround = true;
}

void BossEnemy::Update()
{
	if (trunkpoint >= 100)
	{
		// 死亡状態にする
		exist = false;
	}
	
	// 地面をすり抜けないようにする
	if (param.nextPos.y <= 0)
	{
		param.nextPos.y = 0;
	}

	// 位置修正
	ModifyingPosition();

	// ビヘイビア更新処理
	BehaviorUpdate();

	// 実際の移動処理
	MoveFinish();
	// モデルの向きを決定
	MV1SetRotationYUseDir(modelHandle, param.dir, 0.0f);

}

void BossEnemy::Draw()
{
	// モデルの描画
	MV1DrawModel(modelHandle);
}

/// <summary>
/// 接触処理
/// </summary>
/// <param name="tag"></param>
void BossEnemy::HitObject(Collision* other)
{
	VECTOR sub;

	// プレイヤー
	if (other->GetTag() == CollisionTag::Player)
	{

	}

	// シールド
	if (other->GetTag() == CollisionTag::PlayerShield && !isHit)
	{
		// ゲージの上昇
		IncrementTrunkpoint();

		// 跳ね返る力を設定
		sub = VSub(param.pos, other->GetPos());
		force = VNorm(sub);
		force = VScale(force, BOUND_POWER);

		isHit = true;
	}

	// 弾の接触処理
	if (bulletMgr.IsHitPlayer())
	{
		// ゲージの上昇
		IncrementTrunkpoint();
	}
}

/// <summary>
/// 突進行動
/// </summary>
/// <returns></returns>
bool BossEnemy::AttackAssault()
{
	int maxAssault = json.GetInt(JsonDataType::BossEnemy, "AssaultCount");

	// 一定回数攻撃する
	if (assaultCount < maxAssault)
	{
		if (Vibrate())
		{
			AssaultToPlayer();
		}
		else
		{
			FaceToPlayer();
		}

		return false;
	}
	
	// 次回行動するためにカウントをリセットする
	assaultCount = 0;
	return true;
}

/// <summary>
/// 対象に向かって弾を発射する
/// </summary>
/// <returns></returns>
bool BossEnemy::AttackShotBullet(bool isNormal)
{
	int maxShot = json.GetInt(JsonDataType::BossEnemy, "ShotCount");

	// タイマーの更新
	timer[TimerType::ShotInterval]->Update(deltaTime.GetDeltaTime());
	
	// プレイヤーの方向を向く
	FaceToPlayer();

	// 規定回数を弾を発射する
	if (shotCount <= maxShot)
	{
		ShotBullet(isNormal);
		return false;
	}

	// 次回行動するためカウントをリセットする
	shotCount = 0;
	return true;
}

/// <summary>
/// 踏みつけ攻撃
/// </summary>
/// <returns></returns>
bool BossEnemy::AttackStomp()
{
	int maxStomp = json.GetInt(JsonDataType::BossEnemy, "StompCount");

	// 指定回数踏みつけ攻撃を行う
	if (stompCount <= maxStomp)
	{
		MoveOnTarget(player->GetPos());

		// プレイヤー上空に移動する
		if (isOnTarget)
		{
			if (Vibrate())
			{
				// 移動したら踏みつけ攻撃を行う
				Stomp();
			}
			else
			{
				stompVec = VGet(0, 300, 0);
			}
		}

		// 地面と接触したら
		if (param.nextPos.y <= 0)
		{
			param.nextPos.y = 0;
			isGround = true;
		}

		// 地面と接触している場合
		if (isGround)
		{
			// 一定時間制止する
			timer[TimerType::Landing]->Update(deltaTime.GetDeltaTime());

			// クールタイムを過ぎたら
			if (timer[TimerType::Landing]->IsTimeout())
			{
				// 各タイマーをリセット
				timer[TimerType::VibrateAttack]->Reset();
				timer[TimerType::Landing]->Reset();
				isOnTarget = false;
				isGround = false;
				++stompCount;
				// 一定回数攻撃するまで繰り返す
			}

		}

		return false;
	}

	stompCount = 0;
	return true;
}

/// <summary>
/// 体幹量が半分を超えたか
/// </summary>
/// <returns></returns>
const bool BossEnemy::IsTrunkHarfOver()
{
	int maxTrunk = json.GetInt(JsonDataType::BossEnemy, "MaxTrunk");

	if (trunkpoint >= maxTrunk / 2)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 突進攻撃
/// </summary>
void BossEnemy::AssaultToPlayer()
{
	VECTOR sub = VSub(param.pos, startAssaultPos);
	float inDistance = VSize(sub);
	float speed = json.GetFloat(JsonDataType::BossEnemy, "AssaultSpeed");
	float delta = deltaTime.GetDeltaTime();

	param.nextPos = VAdd(param.nextPos, VScale(param.dir, speed * delta));
	
	// 指定距離突進、キャラクターと接触したら
	if (inDistance >= ASSAULT_DISTANCE)
	{
		// 終了する
		++assaultCount;
		// 振動時のタイマーをリセットする
		timer[TimerType::VibrateAttack]->Reset();
	}
}


void BossEnemy::ShotBullet(bool isNormal)
{

	if (timer[TimerType::ShotInterval]->IsTimeout())
	{
		VECTOR createPos = ZERO_VECTOR;

		float speed = json.GetFloat(JsonDataType::BossEnemy, "BulletSpeed");

		// 通常発射の場合
		if (isNormal)
		{
			// 前方に設置
			createPos = VAdd(param.pos, VScale(param.dir, 50.0f));
			// タイマーをリセット
			timer[TimerType::ShotInterval]->Reset();
			// 弾を生成・発射
			bulletMgr.CreateBullet(createPos, param.dir, speed, ModelType::EnemyBullet);
			// 回数を増加させる
			++shotCount;
		}
		// ショットガンの場合
		else
		{
			timer[TimerType::ShotInterval]->Reset();
			bulletMgr.CreateBulletShotGun(param.pos, param.dir, speed, ModelType::EnemyBullet);
			++shotCount;
		}
	}

}

/// <summary>
/// プレイヤーの方向を向く
/// </summary>
void BossEnemy::FaceToPlayer()
{
	VECTOR sub = VSub(player->GetPos(), param.pos);
	VECTOR dir = VNorm(sub);

	param.dir = dir;
}

/// <summary>
/// 踏みつける
/// </summary>
void BossEnemy::Stomp()
{
	float fallVec = json.GetFloat(JsonDataType::BossEnemy, "StompSpeed");
	stompVec.y -= fallVec;

	param.nextPos = VAdd(param.nextPos, VScale(stompVec, deltaTime.GetDeltaTime()));

}

/// <summary>
/// 
/// </summary>
void BossEnemy::IncrementTrunkpoint()
{
	

	// ゲージの上昇
	if (player->GetShield()->IsJustDefense())
	{
		// ジャストガードの場合は増加量を2倍にする
		trunkpoint += GetDecreaseMagnification() * 2;
	}
	else
	{
		trunkpoint += GetDecreaseMagnification();
	}

}

/// <summary>
/// 減少量を返す
/// </summary>
/// <returns></returns>
float BossEnemy::GetDecreaseMagnification()
{
	std::string state = node->GetName();
	return magnification->GetMagnification(state);
}

/// <summary>
/// 対象の真上に移動する
/// </summary>
/// <param name="target"></param>
/// <returns></returns>
void BossEnemy::MoveOnTarget(VECTOR target)
{
	// 対象の真上に移動した場合は踏みつけ攻撃に入るため処理しない
	if (isOnTarget)
	{
		return;
	}

	float delta = deltaTime.GetDeltaTime();
	// 各値をjsonファイルから取得
	float highPos = json.GetFloat(JsonDataType::BossEnemy, "StompHighPos");
	float speed = json.GetFloat(JsonDataType::BossEnemy, "MoveOnTargetSpeed");
	// 指定地点設定
	VECTOR finishPos = target;
	finishPos.y = finishPos.y + highPos;

	// 対象との距離
	float distance = VSize(VSub(finishPos, param.pos));
	// 制限時間更新
	timer[TimerType::Tracking]->Update(delta);

	isGround = false;

	// 対象の上空に移動する
	VECTOR moveVec = VSub(finishPos, param.pos);
	// 指定高度まで上昇する
	if (param.nextPos.y >= highPos)
	{
		moveVec.y = 0;
	}
	else
	{
		moveVec.y = highPos;
	}
	// 正規化
	moveVec = VNorm(moveVec);
	// 指定の大きさに変更
	moveVec = VScale(moveVec, speed);
	
	// 移動
	param.nextPos = VAdd(param.nextPos, VScale(moveVec, delta));

	// 対象の真上に移動するもしくは一定時間経過すると落下を開始する
	if (distance <= 10 ||
		timer[TimerType::Tracking]->IsTimeout())
	{
		timer[TimerType::Tracking]->Reset();
		isOnTarget = true;
	}

}

/// <summary>
/// 振動させる
/// </summary>
/// <returns></returns>
bool BossEnemy::Vibrate()
{
	float delta = deltaTime.GetDeltaTime();
	float randomX = random.GetRandomFloat(VIBRATE_MIN, VIBRATE_MAX);
	float randomZ = random.GetRandomFloat(VIBRATE_MIN, VIBRATE_MAX);

	// ランダムな方向に移動し続ける
	VECTOR randomForce = VGet(randomX, 0.0f, randomZ);

	timer[TimerType::VibrateAttack]->Update(deltaTime.GetDeltaTime());

	// 指定秒数振動させる
	if (!timer[TimerType::VibrateAttack]->IsTimeout())
	{
		param.nextPos = param.prevPos;
		param.pos = param.prevPos;

		param.nextPos = VAdd(param.nextPos, VScale(randomForce, delta));

		// 突進開始位置を記憶
		startAssaultPos = param.pos;

		return false;
	}
	
	return true;
}

/// <summary>
/// 接触後の反動でスライド
/// </summary>
/// <returns></returns>
bool BossEnemy::Sliding()
{
	float delta = deltaTime.GetDeltaTime();
	// 進行方向とは逆向きの力を設定
	VECTOR friction = force;
	friction = VNorm(friction);
	friction = VScale(friction, REBOUND_RESISTANCE);

	force = VAdd(force, VScale(friction, delta));
	param.nextPos = VAdd(param.nextPos, VScale(force, delta));

	// 反発力が 0 を下回ったら終了する
	if (VSize(force) <= 0)
	{
		force = ZERO_VECTOR;
		isHit = false;
		return true;
	}

	return false;
}

/// <summary>
/// ビヘイビア更新処理
/// </summary>
void BossEnemy::BehaviorUpdate()
{
	//if (activeNode == NULL)
	//{
	//	activeNode = aiTree->Inference(this, behaviorData);
	//}
	//
	//if (activeNode != NULL)
	//{
	//	activeNode = aiTree->Run(this, activeNode, behaviorData);
	//}

	// 行動が決定していない場合は行動を決定する
	if (node == NULL)
	{
		node = aiMgr->InferenceNode();
	}
	else
	{
		node = aiMgr->Update(node);
	}
}

/// <summary>
/// ビヘイビアツリー　ノードの設定
/// </summary>
void BossEnemy::SetupBehavior()
{
	//aiTree->AddNode("", "Root", 0, BehaviorTree::SelectRule::Priority, NULL, NULL);
	//aiTree->AddNode("Root", "Attack", 1, BehaviorTree::SelectRule::SequentialLooping, BossJudgment::GetInstance(), NULL);
	//aiTree->AddNode("Attack", "BulletNormal", 0, BehaviorTree::SelectRule::None, NULL, ActionShotBulletNormal::GetInstance());

	aiMgr->EntryNode("Root", "", 1, 1, BehaviorTree::SelectRule::Priority, NULL);
	aiMgr->EntryNode("Attack", "Root", 2, 1, BehaviorTree::SelectRule::Sequence, NULL);
	aiMgr->EntryNode("Assault", "Attack", 3, 1, BehaviorTree::SelectRule::None, new ActAssault(this));
	//aiMgr->EntryNode("Bullet", "Attack", 3, 2, BehaviorTree::SelectRule::Random, NULL);
	//aiMgr->EntryNode("Stomp", "Attack", 3, 3, BehaviorTree::SelectRule::None, new ActStomp(this));
	//aiMgr->EntryNode("BulletNormal", "Bullet", 4, 1, BehaviorTree::SelectRule::None, new ActBulletNormal(this));
	//aiMgr->EntryNode("BulletShotGun", "Bullet", 4, 1, BehaviorTree::SelectRule::None, new ActBulletShotGun(this));
}
