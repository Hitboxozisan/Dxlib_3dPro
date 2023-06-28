#pragma once

#include "common.h"
#include "CollisionTag.h"
#include "Collision.h"

/// <summary>
/// ゲームオブジェクト基底クラス
/// ゲーム上に存在する全てのオブジェクトはこれを継承する
/// </summary>
class ObjectBase
{
public:
	ObjectBase(CollisionTag tag);
	virtual ~ObjectBase();

	virtual void Initialize();
	virtual void HitObject(Collision* other);

	// ゲッター
	const VECTOR GetPos() const { return param.pos; };
	const bool IsExist() const { return exist; };
	const bool IsHit() const { return isHit; };

protected:
	// オブジェクトのパラメータ
	struct Param
	{
		VECTOR pos;			// 現在の座標（実際の描画位置）
		VECTOR prevPos;		// 1フレーム前の座標
		VECTOR nextPos;		// １フレーム後の座標（次の描画位置）
		VECTOR dir;
		Collision* collision;
		//CollisionTag tag;
	};

	class HitChacker& collideMgr;

	Param param;
	int modelHandle;	// モデル本体
	bool exist;			// 存在するか
	bool isHit;			// 接触したか
	bool noDrawFlame;	// 描画しない状態か
private:
};

