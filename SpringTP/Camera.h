#pragma once
#include "Object.h"
class Camera :
    public Object
{
public:
    Camera(VECTOR _pos);
    virtual ~Camera();
    void Update(float deltaTime);

private:
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

