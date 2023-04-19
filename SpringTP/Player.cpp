#include "Player.h"

const float BodyLength = 10.f;
const float HandLength = 7.5f;
const float BodySize = 2.f;
const float HandSize = 1.25f;
const VECTOR DownVec = VGet(0, -1, 0);
const float MoveAnimSpeed = 0.3f;
const float MoveAnimTop = 0.64f;
const VECTOR ToRightHandVec = VGet(BodySize + HandSize, BodyLength, 0);
const VECTOR ToLeftHandVec = VGet(-(BodySize + HandSize), BodyLength, 0);
const float ConeR = 1.5f;
const float ConeSize = 3.0f;
const int ConeDivNum = 16;
const VECTOR ConeVec = VGet(0, 0, ConeSize);
const unsigned int Green = GetColor(0, 255, 0);
const int AlphaBlendRatio = 160;

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
	moveAnimFlag = true;
	roll = ZERO_F;
	pitch = ZERO_F;
	yaw = ZERO_F;
	bodyAngle = ZERO_F;
	rightHandAngle = ZERO_F;
	leftHandAngle = ZERO_F;
	bodySpring = new SpringBase(bodyPos, DownVec, BodyLength, BodySize, ZERO_F, ZERO_F, ZERO_F);
	rightHandSpring = new SpringBase(rightHandPos, DownVec, HandLength, HandSize, ZERO_F, ZERO_F, ZERO_F);
	leftHandSpring = new SpringBase(leftHandPos, DownVec, HandLength, HandSize, ZERO_F, ZERO_F, ZERO_F);
	conePos = bodyPos;
	conePos.y += ConeR;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	MoveAnim(deltaTime);
	bodySpring->Update(deltaTime);
	rightHandSpring->Update(deltaTime);
	leftHandSpring->Update(deltaTime);
	bodySpring->SetRotate(roll, pitch, yaw);
	rightHandSpring->SetRotate(roll, pitch, yaw);
	leftHandSpring->SetRotate(roll, pitch, yaw);
	//ここから
	if (CheckHitKey(KEY_INPUT_E))
	{
		pitch += 0.2f * deltaTime;
	}
	if (CheckHitKey(KEY_INPUT_Q))
	{
		pitch -= 0.2f * deltaTime;
	}
	//ここまでデバッグ用
	rightHandPos = VAdd(pos, VTransform(ToRightHandVec, MGetRotY(pitch)));
	leftHandPos = VAdd(pos, VTransform(ToLeftHandVec, MGetRotY(pitch)));
	bodySpring->SetPos(bodyPos);
	rightHandSpring->SetPos(rightHandPos);
	leftHandSpring->SetPos(leftHandPos);
}

void Player::Draw()
{
	bodySpring->Draw();
	rightHandSpring->Draw();
	leftHandSpring->Draw();
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, AlphaBlendRatio);
	DrawCone3D(VAdd(conePos, VTransform(ConeVec, MGetRotY(pitch))), conePos, ConeR, ConeDivNum, Green, Green, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, ZERO_I);
	DrawCone3D(VAdd(conePos, VTransform(ConeVec, MGetRotY(pitch))), conePos, ConeR, ConeDivNum, Green, Green, false);
}

void Player::MoveAnim(float deltaTime)
{
	if (moveAnimFlag)
	{
		bodyPos.y += MoveAnimSpeed * deltaTime;
		if (bodyPos.y > BodyLength + MoveAnimTop)
		{
			moveAnimFlag = false;
		}
		leftHandAngle += MoveAnimSpeed * deltaTime;
		rightHandAngle -= MoveAnimSpeed * deltaTime;

	}
	else
	{
		bodyPos.y -= MoveAnimSpeed * deltaTime;
		if (bodyPos.y < BodyLength-MoveAnimTop)
		{
			moveAnimFlag = true;
		}
		leftHandAngle -= MoveAnimSpeed * deltaTime;
		rightHandAngle += MoveAnimSpeed * deltaTime;
	}
	bodySpring->SetRoll(bodyAngle);
	rightHandSpring->SetRoll(rightHandAngle);
	leftHandSpring->SetRoll(leftHandAngle);
}

void Player::AttackAnim(float deltaTime)
{
}

void Player::JumpAnim(float deltaTime)
{
}
