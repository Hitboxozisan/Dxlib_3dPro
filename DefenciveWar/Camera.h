#pragma once
#include "common.h"

/// <summary>
/// �J�����N���X
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

	// �Q�b�^�[
	const VECTOR GetPos() const { return pos; }

private:
	const float DISTANCE_PLAYER = 250.0;						// �v���C���[�Ƃ̋���
	const float INITIAL_YAW =  1.5f;
	const float INITIAL_PITCH = 0.3f;
	const VECTOR INITIAL_POS = VGet(0.0f, 0.0f, 0.0f);			// �����ʒu

	float yaw;
	float pitch;
	VECTOR pos;			// �J�����̈ʒu

};

