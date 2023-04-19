#include "Camera.h"

const float FirstRoll = 0.25f*DX_PI_F;
const float FirstPitch = 0.f;
const float FirstYaw = 0.f;
const float CameraSpeed = 0.05f;
const VECTOR FirstVec = VGet(0, 0, 1);

Camera::Camera(VECTOR _pos)
{
	pos = _pos;
	roll = FirstRoll;
	pitch = FirstPitch;
	yaw = FirstYaw;
	matX = MGetRotX(roll*DX_PI_F);
	matY = MGetRotY(pitch * DX_PI_F);
	matZ = MGetRotZ(yaw * DX_PI_F);
	vec = FirstVec;
	vec = VTransform(vec, matX);
	vec = VTransform(vec, matY);
	vec = VTransform(vec, matZ);
	cameraMoveFlag = false;
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime, VECTOR _pos)
{
	MoveCamera(deltaTime);
	if (cameraMoveFlag)
	{
		matX = MGetRotX(roll * DX_PI_F);
		matY = MGetRotY(pitch * DX_PI_F);
		matZ = MGetRotZ(yaw * DX_PI_F);
		vec = VTransform(FirstVec, matX);
		vec = VTransform(vec, matY);
		vec = VTransform(vec, matZ);
	}
	SetCameraPositionAndTarget_UpVecY(pos, VAdd(pos, vec));
	cameraMoveFlag = false;
}

void Camera::MoveCamera(float deltaTime)
{
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		pitch -= CameraSpeed * deltaTime;
		if (pitch < ZERO_F)
		{
			pitch = RoundRad - pitch;
		}
		cameraMoveFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		pitch += CameraSpeed * deltaTime;
		if (pitch > RoundRad)
		{
			pitch = pitch - RoundRad;
		}
		cameraMoveFlag = true;
		
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		roll += CameraSpeed * deltaTime;
		if (roll > RoundRad)
		{
			roll = roll - RoundRad;
		}
		cameraMoveFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		roll -= CameraSpeed * deltaTime;
		if (roll < ZERO_F)
		{
			roll = RoundRad - roll;
		}
		cameraMoveFlag = true;
		
	}
}
