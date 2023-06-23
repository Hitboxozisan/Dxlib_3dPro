#include "common.h"
#include "UiBase.h"
#include "Singleton.h"
#include "ImageManager.h"


UiBase::UiBase()
	:imageMgr(Singleton<ImageManager>::GetInstance())
	,data(nullptr)
	,exist(false)
{
}

UiBase::~UiBase()
{
}
