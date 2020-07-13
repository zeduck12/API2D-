#include "framework.h"
#include "CGunBarrel.h"

CGunBarrel::CGunBarrel(CGameScene& _rGameScene, CObj* _pOwner, float _fDegree, float _fLength, float _fSpeed)
	:
	CObj(_rGameScene, 0.f, 0.f, 0.f, 0.f, _fSpeed, _fDegree,nullptr),
	m_pOwner(nullptr),
	m_fLength(_fLength)
{
	if (_pOwner) {
		m_pOwner = _pOwner;
		SetX(m_pOwner->GetX());
		SetY(m_pOwner->GetY());
	}
}

CGunBarrel::~CGunBarrel()
{
	Release();
}

void CGunBarrel::Ready(void)
{
}

int CGunBarrel::Update(float _fDeltaTime)
{
	if (m_pOwner) {
		SetX(m_pOwner->GetX());
		SetY(m_pOwner->GetY());
	}
	return 0;
}

void CGunBarrel::LateUpdate(void)
{

}

void CGunBarrel::Render(const HDC& _hdc)
{
	MoveToEx(_hdc, GetStartX(), GetStartY(), nullptr);
	LineTo(_hdc, GetEndX(), GetEndY());
}

void CGunBarrel::Release(void)
{
}
