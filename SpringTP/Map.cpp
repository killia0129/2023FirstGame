#include "Map.h"

const VECTOR MapPos = VGet(0.0f, 0.0f, 50.0f);
const int LineNum = 100;
const float LineDis = 10.0f;
const unsigned int color = GetColor(0, 255, 0);
const int AlphaBlendRatio = 100;

Map::Map()
{
	pos = MapPos;
}

Map::~Map()
{
}

void Map::Draw()
{
	for (int i = ZERO_I; i < LineNum; i++)
	{
		VECTOR lineStart, lineLast;
		lineStart = pos;
		lineLast = pos;
		lineStart.x -= LineNum * LineDis * HALF;
		lineLast.x += LineNum * LineDis * HALF;
		lineStart.z += i * LineDis - LineNum * LineDis * HALF;
		lineLast.z += i * LineDis - LineNum * LineDis * HALF;
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, AlphaBlendRatio);
		DrawLine3D(lineStart, lineLast, color);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, ZERO_I);
	}
	for (int i = ZERO_I; i < LineNum; i++)
	{
		VECTOR lineStart, lineLast;
		lineStart = pos;
		lineLast = pos;
		lineStart.z -= LineNum * LineDis * HALF;
		lineLast.z += LineNum * LineDis * HALF;
		lineStart.x += i * LineDis - LineNum * LineDis * HALF;
		lineLast.x += i * LineDis - LineNum * LineDis * HALF;

		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, AlphaBlendRatio);
		DrawLine3D(lineStart, lineLast, color);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,ZERO_I);
	}
}
