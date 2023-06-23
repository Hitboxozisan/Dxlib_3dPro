#include "common.h"
#include "Ground.h"
#include "ModelManager.h"
#include "Singleton.h"
#include "ModelTypeData.h"

Ground::Ground()
	:modelMgr(Singleton<ModelManager>::GetInstance())
{
}

Ground::~Ground()
{
}

void Ground::Initialize()
{
	pos = ZERO_VECTOR;

	//画像読み込み
	ImageHandle = LoadGraph("Data/Image/EffectBack.png");
	modelHandle = MV1DuplicateModel(modelMgr.GetModelHandle(ModelType::Ground));

	MV1SetPosition(modelHandle, pos);
}

void Ground::Draw()
{
	// 背景画像描画（エフェクトを描画するため）
	DrawGraph(0, 0, ImageHandle, TRUE);

	// ステージライン（線、位置）
	// →、上
	DrawLine3D(VGet(FIELD_POSITION_WEST, 0.0f, FIELD_POSITION_NORTH), VGet(FIELD_POSITION_EAST, 0.0f, FIELD_POSITION_NORTH), GREEN);
	// →、下
	DrawLine3D(VGet(FIELD_POSITION_WEST, 0.0f, FIELD_POSITION_SOUTH), VGet(FIELD_POSITION_EAST, 0.0f, FIELD_POSITION_SOUTH), GREEN);
	// ↓、左
	DrawLine3D(VGet(FIELD_POSITION_WEST, 0.0f, FIELD_POSITION_NORTH), VGet(FIELD_POSITION_WEST, 0.0f, FIELD_POSITION_SOUTH), GREEN);
	// ↓、右
	DrawLine3D(VGet(FIELD_POSITION_EAST, 0.0f, FIELD_POSITION_NORTH), VGet(FIELD_POSITION_EAST, 0.0f, FIELD_POSITION_SOUTH), GREEN);
	//MV1DrawModel(modelHandle);
}
