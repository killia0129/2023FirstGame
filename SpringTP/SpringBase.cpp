#include "SpringBase.h"

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
}
