#pragma once

#include "CollisionTag.h"

/// <summary>
/// シールドクラス
/// プレイヤーが保持する
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

