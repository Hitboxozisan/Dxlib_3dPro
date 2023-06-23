#pragma once

#include "common.h"
#include "CollisionTag.h"
#include "Collision.h"

/// <summary>
/// �Q�[���I�u�W�F�N�g���N���X
/// �Q�[����ɑ��݂���S�ẴI�u�W�F�N�g�͂�����p������
/// </summary>
class ObjectBase
{
public:
	ObjectBase(CollisionTag tag);
	virtual ~ObjectBase();

	virtual void Initialize();
	virtual void HitObject(CollisionTag tag);

	// �Q�b�^�[
	const VECTOR GetPos() const { return param.pos; };
	//const CollisionTag GetTag() const { return param.tag; };
	const bool IsExist() const { return exist; };

protected:
	// �I�u�W�F�N�g�̃p�����[�^
	struct Param
	{
		VECTOR pos;			// ���݂̍��W�i���ۂ̕`��ʒu�j
		VECTOR prevPos;		// 1�t���[���O�̍��W
		VECTOR nextPos;		// �P�t���[����̍��W�i���̕`��ʒu�j
		VECTOR dir;
		Collision* collision;
		//CollisionTag tag;
	};

	class HitChacker& collideMgr;

	Param param;
	int modelHandle;	// ���f���{��
	bool exist;			// ���݂��邩

private:
};

