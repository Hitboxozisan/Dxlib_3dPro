#pragma once

#include "ObjectBase.h"

/// <summary>
/// ���I�I�u�W�F�N�g�N���X
/// �Q�[����ɑ��݂���ړ�����I�u�W�F�N�g�͂�����p������
/// </summary>
class Mover : public ObjectBase
{
public:
	Mover(CollisionTag tag);
	virtual ~Mover();

	virtual void Initialize();

protected:
	class DeltaTime& deltaTime;

	void ModifyingPosition();		// �ʒu���C������
	void MoveFinish();				// ���ۂɃ��f�����ړ�������
private:
};

