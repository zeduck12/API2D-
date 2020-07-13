#include "framework.h"
#include "CBullet.h"
#include "CGameScene.h"
#include "CMonster.h"
#include "CObj.h"

CBullet::CBullet(CGameScene& _rGameScene, CObj* _pOwner, float _fX, float _fY, float _fToX, float _fToY, size_t _iWidth, size_t _iHeight, float _fSpeed, float _fDamage, float _fDegree)
:
	CObj(_rGameScene, _fX, _fY, _iWidth, _iHeight, _fSpeed, _fDegree, Rectangle),
	m_fToX(_fToX),
	m_fToY(_fToY),
	m_fDamage(_fDamage)
{
	if (_pOwner)
	{
		m_pOwner = _pOwner;
		SetX(m_pOwner->GetX());
		SetY(m_pOwner->GetY());
	}
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Ready(void)
{
}

int CBullet::Update(float _fDeltaTime)
{
	// m_fToX   플레이어 위치, m_fX    몬스터 위치
	
	if (m_fToX < m_pOwner->GetX())
		m_fX += m_fSpeed * -1.f;
	else
		m_fX += m_fSpeed;

	m_iHeight -= 0.04f;
	
	return 0;
}

void CBullet::LateUpdate(void)
{
}

void CBullet::Render(const HDC& _hdc)
{
	CObj::Render(_hdc);
}

void CBullet::Release(void)
{
}

