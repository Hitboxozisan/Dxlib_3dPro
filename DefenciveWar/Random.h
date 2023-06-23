#pragma once

/// <summary>
/// ランダムな数値を返すクラス
/// シングルトン
/// </summary>
class Random
{
public:
	Random();
	~Random();
	
	int   GetRandomInt(int min, int max);				// ランダムなint値を返す
	float GetRandomFloat(float min, float max);			// ランダムなfloat値を返す
private:
	
};

