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
};

