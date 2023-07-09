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

	size = 1.5f;
	addSize = 0.5f;
	add = addSize;
}

void BackgroundCube::Create(VECTOR pos, VECTOR dir, float moveSpeed, float scale)
{
	param.nextPos = pos;
	param.pos = pos;
	speed = moveSpeed;
	size = scale;
	exist = true;
}

void BackgroundCube::Update()
{
	float delta = deltaTime.GetDeltaTime();
	// サイズが規定値を超えたら
	if (size + add * delta >= 2.0f) add = -addSize;
	if (size + add * delta <= 1.0f) add = addSize;

	// モデルのサイズを変更する
	size += add * delta;
	MV1SetScale(modelHandle, VGet(size, size, size));


	// 移動処理
	Move();
	// 画面外処理
	OutOfWindow();
	// 位置の設定
	MoveFinish();

}

void BackgroundCube::Draw()
{
	// モデルの描画
	MV1DrawModel(modelHandle);

	DrawFormatString(500, 500, WHITE, "%f", addSize);
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
	if (param.nextPos.x <= FIELD_POSITION_WEST)
	{
		exist = false;
	}

}
