#include "SupportJson.h"
#include "BossEnemy.h"
//#include "BehaviorData.h"
//#include "NodeBase.h"
#include "NodeManager.h"
#include "BossEnemyTimerData.h"
#include "Timer.h"
#include "Random.h"
#include "Singleton.h"
#include "DeltaTime.h"
//#include "BossJudgment.h"
//#include "ActionAssault.h"
#include "ModelManager.h"
#include "Player.h"
#include "EnemyBulletManager.h"
//#include "ActionShotBulletNormal.h"

#include "NodeAssault.h"

#include "KeyManager.h"

using namespace BossTimer;

BossEnemy::BossEnemy(CollisionTag tag, Player* p)
	:random(Singleton<Random>::GetInstance())
	,modelMgr(Singleton<ModelManager>::GetInstance())
	,bulletMgr(Singleton<EnemyBulletManager>::GetInstance())
	,json(Singleton<SupportJson>::GetInstance())
	,key(Singleton<KeyManager>::GetInstance())
	,aiTree(new NodeManager())
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
	// プレイヤー
	if (other->GetTag() == CollisionTag::Player)
	{

	}

	if (other->GetTag() == CollisionTag::Shield)
	{

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

	param.nextPos = VAdd(param.nextPos, VScale(param.dir, speed));
	
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
/// 振動させる
/// </summary>
/// <returns></returns>
bool BossEnemy::Vibrate()
{
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

		param.nextPos = VAdd(param.nextPos, randomForce);

		// 突進開始位置を記憶
		startAssaultPos = param.pos;

		return false;
	}
	
	return true;
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
}

/// <summary>
/// ビヘイビアツリー　ノードの設定
/// </summary>
void BossEnemy::SetupBehavior()
{
	//aiTree->AddNode("", "Root", 0, BehaviorTree::SelectRule::Priority, NULL, NULL);
	//aiTree->AddNode("Root", "Attack", 1, BehaviorTree::SelectRule::SequentialLooping, BossJudgment::GetInstance(), NULL);
	//aiTree->AddNode("Attack", "BulletNormal", 0, BehaviorTree::SelectRule::None, NULL, ActionShotBulletNormal::GetInstance());

	//aiTree->EntryNode();

}
