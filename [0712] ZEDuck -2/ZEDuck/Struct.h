#pragma once

// 위치좌표
typedef struct tagPosition
{
	tagPosition()
	{
		ZeroMemory(this, sizeof(tagPosition));
	}

	tagPosition(float _fX, float _fY)
		:
		m_fX(_fX), m_fY(_fY)
	{ }

	float m_fX;
	float m_fY;

}POSITION;

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