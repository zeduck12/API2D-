#include "framework.h"
#include "CSubBullet.h"
#include "CGameScene.h"
#include "CBullet.h"


CSubBullet::CSubBullet(CGameScene& _rGameScene, size_t _iWidth, size_t _iHeight, float _fSpeed, float _fDamage, float _fDegree)
	:
	CObj(_rGameScene, 0.f, 0.f, _iWidth, _iHeight, _fSpeed, _fDegree, Ellipse),
	m_fToX(0.f),
	m_fToY(0.f),
	m_fDamage(_fDamage)
{
}

CSubBullet::~CSubBullet()
{
}

void CSubBullet::Ready(void)
{
}

int CSubBullet::Update(float _fDeltaTime)
{
	m_fDegree += cfSubBulletSpeed;
	m_fX = m_pBullet->GetX() + cfSubBulletDistance * cosf(GetRadian(m_fDegree));
	m_fY = m_pBullet->GetY() + cfSubBulletDistance * sinf(GetRadian(m_fDegree));
    return 0;
}

void CSubBullet::LateUpdate(void)
{
}

void CSubBullet::Render(const HDC& _hdc)
{
	CObj::Render(_hdc);
}

void CSubBullet::Release(void)
{
}
