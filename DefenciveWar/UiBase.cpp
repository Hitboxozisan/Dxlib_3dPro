#include "common.h"
#include "UiBase.h"
#include "Singleton.h"
#include "ImageManager.h"
#include "DeltaTime.h"


UiBase::UiBase()
	:imageMgr(Singleton<ImageManager>::GetInstance())
	,deltaTime(Singleton<DeltaTime>::GetInstance())
	,data(nullptr)
	,exist(false)
{
}

UiBase::~UiBase()
{
}
