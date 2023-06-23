#pragma once

/// <summary>
/// デルタタイムを管理するクラス
/// シングルトン
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
	bool  isStop;			// ゲームを停止する

};

