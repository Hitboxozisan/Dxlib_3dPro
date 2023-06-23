#pragma once
#include "common.h"

/// <summary>
/// カメラクラス
/// </summary>
class Camera final
{
public:
	Camera();
	~Camera();

	void Initialize();
	void Finalize();
	void Activate();
	void Deactivate();
	//void Update();

	void FollowUpPlayer(VECTOR playerPos);

	// ゲッター
	const VECTOR GetPos() const { return pos; }

private:
	const float DISTANCE_PLAYER = 250.0;						// プレイヤーとの距離
	const float INITIAL_YAW =  1.5f;
	const float INITIAL_PITCH = 0.3f;
	const VECTOR INITIAL_POS = VGet(0.0f, 0.0f, 0.0f);			// 初期位置

	float yaw;
	float pitch;
	VECTOR pos;			// カメラの位置

};

