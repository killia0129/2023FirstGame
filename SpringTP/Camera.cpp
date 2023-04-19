#include "Camera.h"

const float FirstRoll = 0.25f;
const float FirstPitch = 0.f;
const float FirstYaw = 0.f;

Camera::Camera(VECTOR _pos)
{
	pos = _pos;
	roll = FirstRoll;
	pitch = FirstPitch;
	yaw = FirstYaw;
	matX = MGetRotX(roll);
	matY = MGetRotY(pitch);
	matZ = MGetRotZ(yaw);
}

Camera::~Camera()
{
}

void Camera::MoveCamera()
{
}
