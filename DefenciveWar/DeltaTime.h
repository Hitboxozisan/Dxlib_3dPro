#pragma once

/// <summary>
/// �f���^�^�C�����Ǘ�����N���X
/// �V���O���g��
/// </summary>
class DeltaTime
{
public:
	DeltaTime();
	~DeltaTime();

	void   InstrumentationDeltaTime();
	// void   SetDeltaTime(float delta);
	void   SetCount();
	inline float GetDeltaTime() { return deltaTime; }

	const bool IsStop();

private:
	class KeyManager& key;

	int currentCount;
	int prevCount;
	float deltaTime;
	bool  isSlow;
	bool  isStop;			// �Q�[�����~����

};

