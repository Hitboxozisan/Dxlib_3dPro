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
	// �ړ�����
	Move();
	// ��ʊO����
	//OutOfWindow();
	// �ʒu�̐ݒ�
	MoveFinish();

}

void BackgroundCube::Draw()
{
	// ���f���̕`��
	MV1DrawModel(modelHandle);
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
	exist = false;
}
