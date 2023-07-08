#include "Camera.h"

Camera::Camera()
{
	// �`�拗����ݒ�
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
/// �v���C���[��Ǐ]
/// </summary>
/// <param name="playerPos"></param>
void Camera::FollowUpPlayer(VECTOR playerPos)
{
	// �J�����̈ʒu���v�Z
	pos.x = playerPos.x + DISTANCE_PLAYER * cosf(yaw * DX_PI);
	pos.z = playerPos.z + DISTANCE_PLAYER * sinf(yaw * DX_PI);
	pos.y = DISTANCE_PLAYER * sinf(pitch * DX_PI);

	// �J�����̈ʒu�ƌ�����ݒ�
	SetCameraPositionAndTarget_UpVecY(pos, playerPos);
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����
	Effekseer_Sync3DSetting();
}
