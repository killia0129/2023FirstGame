#pragma once
#include"game.h"
//#include"DxLib.h"
class Camera
{
public:
    Camera(VECTOR _pos);
    virtual ~Camera();
    void Update(float deltaTime,VECTOR _pos);

private:
    VECTOR pos;
    float roll;
    float pitch;
    float yaw;
    MATRIX matX;
    MATRIX matY;
    MATRIX matZ;
    VECTOR vec;
    bool cameraMoveFlag;

    void MoveCamera(float deltaTime);
};

