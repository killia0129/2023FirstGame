#pragma once
#include "Object.h"
#include"game.h"
class SpringBase :
    public Object
{
public:
    SpringBase(VECTOR _pos,VECTOR _vec,float _length,float _size,float _roll,float _pitch,float _yaw);
    virtual ~SpringBase();
    void Draw();
    void Update(float deltaTime);
    void SetRoll(float _roll);
    void SetPitch(float _pitch);
    void SetYaw(float _yaw);
    void SetRotate(float _roll, float _pitch, float _yaw);
    void SetPos(VECTOR _pos);

protected:
    VECTOR vec;
    VECTOR normedVec;
    float length;
    float size;
    float roll;
    float pitch;
    float yaw;
    MATRIX matX;
    MATRIX matY;
    MATRIX matZ;
    unsigned int color;
    MATRIX rolled;
    MATRIX pitched;
    MATRIX yawed;
    VECTOR veced;
};

