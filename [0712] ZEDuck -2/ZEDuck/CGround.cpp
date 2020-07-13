#include "framework.h"
#include "CGround.h"

CGround::CGround(const GROUND_INFO& _rInfo)
	:
	m_tInfo(_rInfo),
	m_fSpeed(8.f)
{
}

CGround::~CGround()
{
	Release();
}

void CGround::Ready(void)
{
}

int CGround::Update(float _fDeltaTime)
{
	m_tInfo.fX -= m_fSpeed;

	return 0;
}

void CGround::LateUpdate(void)
{
}

void CGround::Render(const HDC& _hdc)
{
	Rectangle(_hdc, m_tInfo.fX - (m_tInfo.iWidth >> 1), m_tInfo.fY -(m_tInfo.iHeight >> 1),
		m_tInfo.fX + (m_tInfo.iWidth >> 1), m_tInfo.fY + (m_tInfo.iHeight >> 1));
}

void CGround::Release(void)
{
}
