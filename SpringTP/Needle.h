#pragma once
#include "EnemyBase.h"
class Needle :
    public EnemyBase
{
public:
    Needle(VECTOR _pos, int _tag);
    virtual ~Needle();
    void Update(float deltaTime);

private:
    float speed;
    VECTOR normedVec;
};

