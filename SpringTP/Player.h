#pragma once
#include "Object.h"
#include"SpringBase.h"
class Player :
    public Object
{
public:
    Player(VECTOR _pos);
    virtual ~Player();
    void Update(float deltaTime);

private:
    SpringBase* bodySpring;
    SpringBase* rightHandSpring;
    SpringBase* leftHandSpring;
    VECTOR bodyPos;
    VECTOR rightHandPos;
    VECTOR leftHandPos;
    void MoveAnim(float deltaTime);
    void AttackAnim(float deltaTime);
    void JumpAnim(float deltaTime);
    bool inAttack;
    bool inJump;
};

