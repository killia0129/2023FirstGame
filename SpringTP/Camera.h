#pragma once
#include "Object.h"
class Camera :
    public Object
{
public:
    Camera(VECTOR pos);
    virtual ~Camera();
    void MoveCamera();

private:
    float roll;
    float pitch;
    float yaw;
    MATRIX matX;
    MATRIX matY;
    MATRIX matZ;
};

