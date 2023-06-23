#include "common.h"
#include "Shield.h"

Shield::Shield()
{
}

Shield::~Shield()
{
}

void Shield::Initialize()
{
	param.pos = ZERO_VECTOR;
	param.tag = CollisionTag::Shield;
}
