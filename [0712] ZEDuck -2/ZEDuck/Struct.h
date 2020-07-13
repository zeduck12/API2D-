#pragma once

// ���� ��ǥ
typedef struct tagLinePoint
{
	tagLinePoint()
	{
		// ������ stl ���� ����ü �ȿ� �־����� ���θ޸� x
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