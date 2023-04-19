#include "Player.h"

const float BodyLength = 10.f;
const float HandLength = 7.5f;
const float BodySize = 2.f;
const float HandSize = 1.25f;
const VECTOR DownVec = VGet(0, -1, 0);
const float MoveAnimSpeed = 0.1f;
const float MoveAnimTop = 0.16f;
const VECTOR ToRightHandVec = VGet(BodySize + HandSize, BodyLength, 0);
const VECTOR ToLeftHandVec = VGet(-(BodySize + HandSize), BodyLength, 0);

Player::Player(VECTOR _pos)
{
	pos = _pos;
	bodyPos = pos;
	bodyPos.y += BodyLength;
	rightHandPos = bodyPos;
	leftHandPos = bodyPos;
	rightHandPos.x += BodySize + HandSize;
	leftHandPos.x -= BodySize + HandSize;
	inAttack = false;
	inJump = false;
	moveAnimFlag = false;
	roll = ZERO_F;
	pitch = ZERO_F;
	yaw = ZERO_F;
	bodyAngle = ZERO_F;
	rightHandAngle = ZERO_F;
	leftHandAngle = ZERO_F;
	bodySpring = new SpringBase(bodyPos, DownVec, BodyLength, BodySize, ZERO_F, ZERO_F, ZERO_F);
	rightHandSpring = new SpringBase(rightHandPos, DownVec, HandLength, HandSize, ZERO_F, ZERO_F, ZERO_F);
	leftHandSpring = new SpringBase(leftHandPos, DownVec, HandLength, HandSize, ZERO_F, ZERO_F, ZERO_F);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	MoveAnim(deltaTime);
	bodySpring->Update(deltaTime);
	bodySpring->SetRotate(roll, pitch, yaw);
	if (CheckHitKey(KEY_INPUT_E))
	{
		pitch += 0.1f * deltaTime;
	}
	if (CheckHitKey(KEY_INPUT_Q))
	{
		pitch -= 0.1f * deltaTime;
	}
	rightHandPos = VAdd(pos, VTransform(ToRightHandVec, MGetRotY(pitch)));
	leftHandPos = VAdd(pos, VTransform(ToLeftHandVec, MGetRotY(pitch)));
	rightHandSpring->SetPos(rightHandPos);
	leftHandSpring->SetPos(leftHandPos);
}

void Player::Draw()
{
	bodySpring->Draw();
	rightHandSpring->Draw();
	leftHandSpring->Draw();
}

void Player::MoveAnim(float deltaTime)
{
	if (moveAnimFlag)
	{
		bodyAngle += MoveAnimSpeed * deltaTime;
		if (bodyAngle > MoveAnimTop)
		{
			moveAnimFlag = false;
		}
	}
	else
	{
		bodyAngle -= MoveAnimSpeed * deltaTime;
		if (bodyAngle < -MoveAnimTop)
		{
			moveAnimFlag = true;
		}
	}
	bodySpring->SetRoll(bodyAngle);
}

void Player::AttackAnim(float deltaTime)
{
}

void Player::JumpAnim(float deltaTime)
{
}
