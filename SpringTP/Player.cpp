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
const float PlayerSpeed = 2.f;
const VECTOR AheadVec = VGet(0, 0, PlayerSpeed);
const VECTOR BackVec = VGet(0, 0, -PlayerSpeed);
const VECTOR RightVec = VGet(PlayerSpeed, 0, 0);
const VECTOR LeftVec = VGet(-PlayerSpeed, 0, 0);

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
	if (CheckHitKey(KEY_INPUT_W))
	{

	}
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
	float tmp = bodyPos.y;
	bodyPos = pos;
	bodyPos.y = tmp;
	bodySpring->SetPos(bodyPos);
	rightHandSpring->SetPos(rightHandPos);
	leftHandSpring->SetPos(leftHandPos);
	conePos = bodyPos;
	conePos.y += ConeR;
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

void Player::Move(float cameraPitch,float deltaTime)
{
	MATRIX cameraMatY = MGetRotY(cameraPitch*DX_PI_F);
	VECTOR moveVec = ZERO_POS;
	if (CheckHitKey(KEY_INPUT_W))
	{
		moveVec = VAdd(moveVec, AheadVec);
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		moveVec = VAdd(moveVec, BackVec);
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		moveVec = VAdd(moveVec, LeftVec);
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		moveVec = VAdd(moveVec, RightVec);
	}
	if (VSize(moveVec) != 0.f)
	{
		moveVec = VTransform(moveVec, cameraMatY);
		moveVec = VNorm(moveVec);
		moveVec = VScale(moveVec, PlayerSpeed * deltaTime);
		pos = VAdd(pos, moveVec);
	}

	DrawFormatString(10, 10, GetColor(255, 255, 255), "moveVec(x,y,z):(%f, %f, %f)", moveVec.x, moveVec.y, moveVec.z);
	DrawFormatString(10, 50, GetColor(255, 255, 255), "cameraPitch:%f", cameraPitch);
	//bodyPos = pos;
	//bodyPos.y += BodyLength;   
	//rightHandPos = VAdd(pos, VTransform(ToRightHandVec, MGetRotY(pitch)));
	//leftHandPos = VAdd(pos, VTransform(ToLeftHandVec, MGetRotY(pitch)));
	//bodySpring->SetPos(bodyPos);
	//rightHandSpring->SetPos(rightHandPos);
	//leftHandSpring->SetPos(leftHandPos);
	//conePos = bodyPos;
	//conePos.y += ConeR;
}

VECTOR Player::GetPos()
{
	return pos;
}
