#pragma once
#include "EnemyBase.h"
class Meteor :
    public EnemyBase
{
public:
    Meteor(VECTOR _pos, int _tag,bool _waveFlag);
    virtual ~Meteor();
    void Update(float deltaTime);

private:
    bool waveFlag;
    float waveController;
};

