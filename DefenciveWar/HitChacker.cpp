#include "HitChacker.h"
#include "ModelTypeData.h"


HitChacker::HitChacker()
{
	
}

HitChacker::~HitChacker()
{
}

void HitChacker::Update()
{
	for (auto itr : collideVec)
	{
		itr->Update();
	}
	Chack();
}

void HitChacker::Draw()
{
	for (auto itr : collideVec)
	{
		itr->DrawCollision();
	}
}

void HitChacker::Chack()
{
	for (auto itr : collideVec)
	{
		for (auto itr2 : collideVec)
		{
			// オブジェクトが存在しないもしくは
			// 同じオブジェクトかベクターの終端に来たらスキップ
			if(!itr->IsExist() ||
				itr == itr2 || 
				itr2 == NULL)
			{
				continue;
			}
			else if ((*itr).Chack(itr2))
			{
				(*itr).HitObject(itr2->GetCollision());
			}
		}
	}

}

/// <summary>
/// 
/// </summary>
/// <param name="collide"></param>
void HitChacker::EntryCollide(Collision* collide)
{
	collideVec.push_back(collide);
}
