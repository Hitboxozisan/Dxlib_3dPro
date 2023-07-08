#include "BackgroundCube.h"
#include "Singleton.h"
#include "ModelManager.h"
#include "DeltaTime.h"

BackgroundCube::BackgroundCube(CollisionTag tag, ModelType mt)
	:Mover(tag)
	,modelMgr(Singleton<ModelManager>::GetInstance())
{
	// 当たり判定は存在しない
	param.collision->data.radius = 0;
	// モデルの読み込み
	modelHandle = MV1DuplicateModel(modelMgr.GetModelHandle(mt));

	// 初期化
	Initialize();
}

BackgroundCube::~BackgroundCube()
{
}

void BackgroundCube::Initialize()
{
	param.nextPos = ZERO_VECTOR;
	param.pos = ZERO_VECTOR;
	param.dir = ZERO_VECTOR;
	param.collision->exist = false;
	exist = false;
}

void BackgroundCube::Create(VECTOR pos, VECTOR dir, float moveSpeed)
{
	param.nextPos = pos;
	param.pos = pos;
	speed = moveSpeed;
	exist = true;
}

void BackgroundCube::Update()
{
	// 移動処理
	Move();
	// 画面外処理
	//OutOfWindow();
	// 位置の設定
	MoveFinish();

}

void BackgroundCube::Draw()
{
	// モデルの描画
	MV1DrawModel(modelHandle);
}

void BackgroundCube::Move()
{
	VECTOR moveLeftVec = VGet(-1, 0, 0);

	// 一定速度で画面左側に向かって移動する
	param.nextPos = VAdd(param.nextPos, VScale(moveLeftVec, speed * deltaTime.GetDeltaTime()));
}

void BackgroundCube::OutOfWindow()
{
	// 画面外に出た場合存在を消去する
	exist = false;
}
