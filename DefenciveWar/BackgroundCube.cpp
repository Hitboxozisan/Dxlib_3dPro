#include "BackgroundCube.h"
#include "Singleton.h"
#include "ModelManager.h"
#include "DeltaTime.h"

BackgroundCube::BackgroundCube(CollisionTag tag, ModelType mt)
	:Mover(tag)
	,modelMgr(Singleton<ModelManager>::GetInstance())
{
	// �����蔻��͑��݂��Ȃ�
	param.collision->data.radius = 0;
	// ���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(modelMgr.GetModelHandle(mt));

	// ������
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
	// �T�C�Y���K��l�𒴂�����
	if (size + add * delta >= 2.0f) add = -addSize;
	if (size + add * delta <= 1.0f) add = addSize;

	// ���f���̃T�C�Y��ύX����
	size += add * delta;
	MV1SetScale(modelHandle, VGet(size, size, size));


	// �ړ�����
	Move();
	// ��ʊO����
	OutOfWindow();
	// �ʒu�̐ݒ�
	MoveFinish();

}

void BackgroundCube::Draw()
{
	// ���f���̕`��
	MV1DrawModel(modelHandle);

	DrawFormatString(500, 500, WHITE, "%f", addSize);
}

void BackgroundCube::Move()
{
	VECTOR moveLeftVec = VGet(-1, 0, 0);

	// ��葬�x�ŉ�ʍ����Ɍ������Ĉړ�����
	param.nextPos = VAdd(param.nextPos, VScale(moveLeftVec, speed * deltaTime.GetDeltaTime()));
}

void BackgroundCube::OutOfWindow()
{
	// ��ʊO�ɏo���ꍇ���݂���������
	if (param.nextPos.x <= FIELD_POSITION_WEST)
	{
		exist = false;
	}

}
