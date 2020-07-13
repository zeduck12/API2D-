#pragma once

// 선의 좌표
typedef struct tagLinePoint
{
	tagLinePoint()
	{
		// 포인터 stl 들어간거 구조체 안에 넣었을때 제로메모리 x
		ZeroMemory(this, sizeof(tagLinePoint));
	}

	tagLinePoint(float _fX, float _fY)
		:
		fX(_fX), fY(_fY)
	{ }

	float fX;
	float fY;

}LINEPOS;

typedef struct tagLineInfo
{
	tagLineInfo()
	{
		ZeroMemory(this, sizeof(tagLineInfo));
	}

	tagLineInfo(const LINEPOS& _rLeftPos, const LINEPOS& _rRightPos)
		:
		tLPoint(_rLeftPos), tRPoint(_rRightPos)
	{ }

	LINEPOS tLPoint;
	LINEPOS tRPoint;

}LINEINFO;