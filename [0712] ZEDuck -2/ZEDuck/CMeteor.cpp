#include "framework.h"
#include "CMeteor.h"

CMeteor::CMeteor(CGameScene& _rGameScene, CObj* _pOwner, float _fX, float _fY, float _fToX, float _fToY, size_t _iWidth, size_t _iHeight, float _fSpeed, float _fDamage, float _fDegree)
	:
	CObj(_rGameScene, _fX, _fY, _iWidth, _iHeight, _fSpeed, _fDegree, Ellipse),
	m_fToX(_fToX),
	m_fToY(_fToY),
	m_fDamage(_fDamage)
{
	m_fX = _fX;
	m_fY = _fY;
}

CMeteor::~CMeteor()
{
	Release();
}

void CMeteor::Ready(void)
{
}

int CMeteor::Update(float _fDeltaTime)
{
	if (m_fY > m_fToY)
		m_fY = m_fToY;

	m_fY += m_fSpeed;
	return 0;
}

void CMeteor::LateUpdate(void)
{
}

void CMeteor::Render(const HDC& _hdc)
{
	CObj::Render(_hdc);
}

void CMeteor::Release(void)
{
}
