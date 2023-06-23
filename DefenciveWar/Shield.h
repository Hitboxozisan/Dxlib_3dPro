#pragma once

#include "CollisionTag.h"

/// <summary>
/// �V�[���h�N���X
/// �v���C���[���ێ�����
/// </summary>
class Shield final
{
public:
	Shield();
	~Shield();

	void Initialize();

private:
	struct Param
	{
		VECTOR pos;
		CollisionTag tag;
	};

	Param param;
};

