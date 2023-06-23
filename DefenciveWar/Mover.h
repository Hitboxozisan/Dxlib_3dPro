#pragma once

#include "ObjectBase.h"

/// <summary>
/// 動的オブジェクトクラス
/// ゲーム上に存在する移動するオブジェクトはこれを継承する
/// </summary>
class Mover : public ObjectBase
{
public:
	Mover(CollisionTag tag);
	virtual ~Mover();

	virtual void Initialize();

protected:
	class DeltaTime& deltaTime;

	void ModifyingPosition();		// 位置を修正する
	void MoveFinish();				// 実際にモデルを移動させる
private:
};

