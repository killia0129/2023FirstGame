#include "SpringBase.h"
#include"DxLib.h"


const int SpringRollNum = 5;
const float SpringRollRatio = 0.25f;
const float SpringRollMidDiff = 0.001f;
const int SpringRollDivNum = 16;

SpringBase::SpringBase(VECTOR _pos, VECTOR _vec, float _length, float _size, float _roll, float _pitch, float _yaw)
{
	pos = _pos;
	vec = _vec;
	normedVec = VNorm(vec);
	length = _length;
	size = _size;
	roll = _roll;
	pitch = _pitch;
	yaw = _yaw;
	matX = MGetRotX(roll);
	matY = MGetRotY(pitch);
	matZ = MGetRotZ(yaw);
	vec = VTransform(normedVec, matX);
	vec = VTransform(vec, matY);
	vec = VTransform(vec, matZ);
	color = GetColor(0, 255, 0);
}

SpringBase::~SpringBase()
{
}

void SpringBase::Draw()
{
	VECTOR lineLast = VAdd(pos, VScale(normedVec, length));
	DrawLine3D(pos, lineLast, color);
	for (int i = ZERO_I; i < SpringRollNum; i++)
	{
		DrawCone3D(VAdd(pos, VScale(vec, length*SpringRollRatio * (float)i)), VAdd(pos, VScale(vec, length * SpringRollRatio  * (float)i + SpringRollMidDiff)), size,SpringRollDivNum, color, color, false);
	}
}

void SpringBase::Update(float deltaTime)
{
}
