#include "Needle.h"

const VECTOR FirstNormedVec = VGet(1, 0, 0);
const float NeedleSpeed = 1.f;
const int MaxHP = 2;

Needle::Needle(VECTOR _pos, int _tag)
{
	pos = _pos;
	tag = _tag;
	aheadVec = VSub(ZERO_POS, pos);
	aheadVec = VNorm(aheadVec);
	speed = NeedleSpeed;
	tag = NEEDLE;
	normedVec = aheadVec;
	HP = MaxHP;
}

Needle::~Needle()
{
}

void Needle::Update(float deltaTime)
{
	pos = VAdd(pos, VScale(aheadVec, NeedleSpeed));
	if (HP <= ZERO_I)
	{
		isAlive = false;
	}
}
