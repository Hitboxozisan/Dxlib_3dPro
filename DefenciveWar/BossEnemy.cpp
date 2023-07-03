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
}

void BossEnemy::Update()
{

	//if (key.CheckPressed(KEY_INPUT_0) &&
	//	trunkpoint <= 100)
	//{
	//	if (trunkpoint >= 100)
	//	{
	//		trunkpoint = 100;
	//	}
	//	trunkpoint++;
	//}
	//if (key.CheckPressed(KEY_INPUT_1) &&
	//	trunkpoint >= 0)
	//{
	//	if (trunkpoint <= 0)
	//	{
	//		trunkpoint = 0;
	//	}
	//	trunkpoint--;
	//}

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
	if (other->GetTag() == CollisionTag::Shield)
	{
		float decrease;

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

		// 跳ね返る力を設定
		sub = VSub(param.pos, other->GetPos());
		force = VNorm(sub);
		force = VScale(force, BOUND_POWER);

		isHit = true;
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
	
	return true;
}

/// <summary>
/// 対象に向かって弾を発射する
/// </summary>
/// <returns></returns>
bool BossEnemy::AttackShotBullet()
{
	int maxShot = json.GetInt(JsonDataType::BossEnemy, "ShotCount");
	float speed = json.GetFloat(JsonDataType::BossEnemy, "BulletSpeed");

	// タイマーの更新
	timer[TimerType::ShotInterval]->Update(deltaTime.GetDeltaTime());
	
	// プレイヤーの方向を向く
	FaceToPlayer();

	// 規定回数を弾を発射する
	if (shotCount < maxShot &&
		timer[TimerType::ShotInterval]->IsTimeout())
	{
		// 前方に設置
		VECTOR createPos = VAdd(param.pos, VScale(param.dir, 50.0f));

		// タイマーをリセット
		timer[TimerType::ShotInterval]->Reset();

		// 弾を生成・発射
		bulletMgr.CreateBullet(createPos, param.dir, speed, ModelType::EnemyBullet);
	
		// 回数を増加させる
		++shotCount;

		return false;
	}

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
/// 減少量を返す
/// </summary>
/// <returns></returns>
float BossEnemy::GetDecreaseMagnification()
{
	std::string state = node->GetName();
	return magnification->GetMagnification(state);
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
	VECTOR friction = force;
	friction = VNorm(friction);
	friction = VScale(friction, REBOUND_RESISTANCE);

	force = VAdd(force, VScale(friction, delta));
	param.nextPos = VAdd(param.nextPos, force);

	// 反発力が 0 を下回ったら終了する
	if (VSize(force) <= 0)
	{
		force = ZERO_VECTOR;
		isHit = true;
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
	if (node == nullptr)
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
	aiMgr->EntryNode("Attack", "Root", 2, 1, BehaviorTree::SelectRule::Priority, NULL);
	aiMgr->EntryNode("Assault", "Attack", 3, 1, BehaviorTree::SelectRule::Random, new ActAssault(this));
}
