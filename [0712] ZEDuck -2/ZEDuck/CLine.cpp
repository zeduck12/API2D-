#include "framework.h"
#include "CLine.h"

CLine::CLine()
{
}

CLine::CLine(const LINEINFO& rLineInfo)
	:
	m_tInfo(rLineInfo)
{
}

CLine::~CLine()
{
}

void CLine::Render_Line(const HDC& _hdc)
{
	MoveToEx(_hdc, int(m_tInfo.tLPoint.fX), int(m_tInfo.tLPoint.fY), nullptr);
	LineTo(_hdc, int(m_tInfo.tRPoint.fX), int(m_tInfo.tRPoint.fY));
}

