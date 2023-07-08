#include "Camera.h"

Camera::Camera()
{
	// 描画距離を設定
	SetCameraNearFar(1, 1000);
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
}

void Camera::Finalize()
{
}

void Camera::Activate()
{
	pos = INITIAL_POS;
	yaw = INITIAL_YAW;
	pitch = INITIAL_PITCH;
}

void Camera::Deactivate()
{
}

/// <summary>
/// プレイヤーを追従
/// </summary>
/// <param name="playerPos"></param>
void Camera::FollowUpPlayer(VECTOR playerPos)
{
	// カメラの位置を計算
	pos.x = playerPos.x + DISTANCE_PLAYER * cosf(yaw * DX_PI);
	pos.z = playerPos.z + DISTANCE_PLAYER * sinf(yaw * DX_PI);
	pos.y = DISTANCE_PLAYER * sinf(pitch * DX_PI);

	// カメラの位置と向きを設定
	SetCameraPositionAndTarget_UpVecY(pos, playerPos);
	// DXライブラリのカメラとEffekseerのカメラを同期する
	Effekseer_Sync3DSetting();
}
