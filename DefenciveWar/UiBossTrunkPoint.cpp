#include "common.h"
#include "UiBossTrunkPoint.h"
#include "Timer.h"
#include "Singleton.h"
#include "ImageManager.h"
#include "SceneGame.h"
#include "BossEnemy.h"

UiBossTrunkPoint::UiBossTrunkPoint(class SceneGame* objData)
	:imageMgr(Singleton<ImageManager>::GetInstance())
	, vibrateTimer(new Timer(VIBRATE_TIME))
{
	data = objData;

	param.handle = imageMgr.GetImage(ImageType::TrunkGaugeCeneter);
	edge[Edge_Right].handle = imageMgr.GetImage(ImageType::TrunkGaugeEdge);
	edge[Edge_Left].handle = imageMgr.GetImage(ImageType::TrunkGaugeEdge);

	gaugeLength = 460;
}

UiBossTrunkPoint::~UiBossTrunkPoint()
{
}

void UiBossTrunkPoint::Initialize()
{
	float gaugeRX = gauge[Gauge_Left].posL.x + gaugeLength;
	float gaugeLX = (gauge[Gauge_Right].posL.x - 10) + gaugeLength;

	// äeç¿ïWê›íË
	// Ui
	param.pos = INITIAL_POS_UI;
	param.prevPos = param.pos;
	// Uií[
	edge[Edge_Right].pos = VGet(param.pos.x + gaugeLength + 15, param.pos.y, 0);
	edge[Edge_Left].pos = VGet(param.pos.x - gaugeLength - 15, param.pos.y, 0);
	// ÉQÅ[ÉW
	gauge[Gauge_Right].posL = INITIAL_POS_GAUGE;
	gauge[Gauge_Right].prevPosL = gauge[Gauge_Right].posL;
	gauge[Gauge_Right].posR = VGet(gaugeRX, 110, 0);
	gauge[Gauge_Right].prevPosR = gauge[Gauge_Right].posR;
	gauge[Gauge_Left].posR = VGet(gaugeLX, 110, 0);
}

void UiBossTrunkPoint::Update()
{
	float trunkpoint = data->GetBossEnemy()->GetTrunkPoint();
	float maxTrunk = 100;

	gauge[Gauge_Right].posR.x = gauge[Gauge_Right].posL.x + gaugeLength * (trunkpoint / maxTrunk);
	gauge[Gauge_Left].posR.x = (gauge[Gauge_Right].posL.x - 10) + gaugeLength * (-trunkpoint / maxTrunk);
}

void UiBossTrunkPoint::Draw()
{
	float trunkpoint = data->GetBossEnemy()->GetTrunkPoint();
	float trunkCenterSize = imageMgr.GetImageSize(ImageType::TrunkGaugeCeneter);
	float trunkBackSize = imageMgr.GetImageSize(ImageType::TrunkGaugeBack);
	float trunkEdgeSize = imageMgr.GetImageSize(ImageType::TrunkGaugeEdge);

	// ílÇ™ 0 ÇÃèÍçáÇÕï`âÊÇµÇ»Ç¢
	if (trunkpoint == 0)
	{
		return;
	}

	int subY = gauge[Gauge_Right].posL.y + ((gauge[Gauge_Right].posR.y - gauge[Gauge_Right].posL.y) / 2);
	unsigned int color = GetColor(246, 150 - trunkpoint, 0);

	// ÉQÅ[ÉWîwåiï`âÊ
	//DrawRotaGraph(param.pos.x, param.pos.y, trunkBackSize, 0.0f, , TRUE);

	// ÉQÅ[ÉWï`âÊ
	// âEë§
	DrawBox(gauge[Gauge_Right].posL.x, gauge[Gauge_Right].posL.y, gauge[Gauge_Right].posR.x, gauge[Gauge_Right].posR.y, color, TRUE);
	DrawTriangle(gauge[Gauge_Right].posR.x, gauge[Gauge_Right].posL.y,
		gauge[Gauge_Right].posR.x, gauge[Gauge_Right].posR.y,
		gauge[Gauge_Right].posR.x + 20, subY,
		color, TRUE);
	// ç∂ë§
	DrawBox(gauge[Gauge_Right].posL.x - 5, gauge[Gauge_Right].posL.y, gauge[Gauge_Left].posR.x, gauge[Gauge_Right].posR.y, color, TRUE);
	DrawTriangle(gauge[Gauge_Left].posR.x, gauge[Gauge_Right].posL.y,
		gauge[Gauge_Left].posR.x, gauge[Gauge_Right].posR.y,
		gauge[Gauge_Left].posR.x - 20, subY,
		color, TRUE);

	// ÉQÅ[ÉWíÜêSï`âÊ
	DrawRotaGraph(param.pos.x, param.pos.y, trunkCenterSize, 0.0f * DX_PI, param.handle, TRUE);
	// ÉQÅ[ÉWí[ï`âÊ
	DrawRotaGraph(edge[Edge_Right].pos.x, edge[Edge_Right].pos.y, trunkEdgeSize, 0.5f * DX_PI, edge[Edge_Right].handle, TRUE);
	DrawRotaGraph(edge[Edge_Left].pos.x, edge[Edge_Left].pos.y, trunkEdgeSize, -0.5f * DX_PI, edge[Edge_Left].handle, TRUE);
}

void UiBossTrunkPoint::UpdateValue()
{
}
