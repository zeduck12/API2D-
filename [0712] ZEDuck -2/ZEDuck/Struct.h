#pragma once

// ��ġ��ǥ
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