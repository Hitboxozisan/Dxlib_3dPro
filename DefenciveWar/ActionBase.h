#pragma once

class ActionBase
{
public:

	// 実行情報
	enum State
	{
		RUN,			// 実行中
		FAILED,			// 実行失敗
		COMPLETE,		// 実行成功
	};

	// 実行処理
	virtual State Run(class BossEnemy* boss) = 0;

private:
};

