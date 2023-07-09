#include "common.h"
#include "Ground.h"
#include "ModelManager.h"
#include "Singleton.h"
#include "ModelTypeData.h"
#include "BackgroundCubeManager.h"

Ground::Ground()
	:modelMgr(Singleton<ModelManager>::GetInstance())
	, bgCubeMgr(new BackgroundCubeManager(ModelType::BgCube))
{
}

Ground::~Ground()
{
}

void Ground::Initialize()
{
	pos = ZERO_VECTOR;

	//�摜�ǂݍ���
	ImageHandle = LoadGraph("Data/Image/EffectBack.png");
	modelHandle = MV1DuplicateModel(modelMgr.GetModelHandle(ModelType::Ground));

	MV1SetPosition(modelHandle, pos);
}

void Ground::Update()
{
	//bgCubeMgr->Update();
}

void Ground::Draw()
{
	// �w�i�摜�`��i�G�t�F�N�g��`�悷�邽�߁j
	DrawGraph(0, 0, ImageHandle, TRUE);

	//bgCubeMgr->Draw();

	// �X�e�[�W���C���i���A�ʒu�j
	// ���A��
	DrawLine3D(VGet(FIELD_POSITION_WEST, 0.0f, FIELD_POSITION_NORTH), VGet(FIELD_POSITION_EAST, 0.0f, FIELD_POSITION_NORTH), GREEN);
	// ���A��
	DrawLine3D(VGet(FIELD_POSITION_WEST, 0.0f, FIELD_POSITION_SOUTH), VGet(FIELD_POSITION_EAST, 0.0f, FIELD_POSITION_SOUTH), GREEN);
	// ���A��
	DrawLine3D(VGet(FIELD_POSITION_WEST, 0.0f, FIELD_POSITION_NORTH), VGet(FIELD_POSITION_WEST, 0.0f, FIELD_POSITION_SOUTH), GREEN);
	// ���A�E
	DrawLine3D(VGet(FIELD_POSITION_EAST, 0.0f, FIELD_POSITION_NORTH), VGet(FIELD_POSITION_EAST, 0.0f, FIELD_POSITION_SOUTH), GREEN);
	//MV1DrawModel(modelHandle);
}
