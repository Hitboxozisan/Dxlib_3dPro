#pragma once

#include "UiBase.h"

class UiBossTrunkPoint final : public UiBase
{
public:
	UiBossTrunkPoint(class SceneGame* objData);
	~UiBossTrunkPoint();

	enum EdgeType
	{
		Edge_Right = 0,
		Edge_Left,

		EdgeAmount,
	};

	enum GaugeType
	{
		Gauge_Right = 0,
		Gauge_Left,

		GaugeAmount
	};

	void Initialize();
	void Update();
	void Draw();

private:
	const VECTOR INITIAL_POS_UI = VGet(937, 100, 0);
	const VECTOR INITIAL_POS_GAUGE = VGet(943, 90, 0);
	const VECTOR VIBRATE_UI = VGet(20, 20, 0);
	const float VIBRATE_TIME = 0.3f;

	struct Edge
	{
		VECTOR pos;
		VECTOR prevPos;
		int handle;
	};

	struct Gauge
	{
		VECTOR posL;
		VECTOR posR;
		VECTOR prevPosL;
		VECTOR prevPosR;
	};

	int gaugeLength;

	class ImageManager& imageMgr;
	class Timer* vibrateTimer;

	Edge edge[EdgeAmount];
	Gauge gauge[GaugeAmount];

	void UpdateValue();
};

