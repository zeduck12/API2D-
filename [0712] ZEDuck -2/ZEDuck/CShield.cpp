#include "framework.h"
#include "CShield.h"
#include "CGameScene.h"
#include "CPlayer.h"

CShield::CShield(CGameScene& _rGameScene, size_t _iWidth /*= ciShieldSize*/, size_t _iHeight /*= ciShieldSize*/, float _fSpeed /*= ciShieldSpeed*/, float _fDegree /*=0.f*/)
    :
    CObj(_rGameScene, 0.f, 0.f, _iWidth, _iHeight, _fSpeed, _fDegree, Ellipse)
{
}

CShield::~CShield()
{
    Release();
}

void CShield::Ready(void)
{
}

int CShield::Update(float _fDeltaTime)
{
    m_fDegree += 10.f;
    m_fX = GetGameScene().GetPlayer()->GetX() + cfShieldDistance * cosf(GetRadian(m_fDegree));
    m_fY = GetGameScene().GetPlayer()->GetY() + cfShieldDistance * sinf(GetRadian(m_fDegree));
    return 0;
}

void CShield::LateUpdate(void)
{
}

void CShield::Render(const HDC& _hdc)
{
    CObj::Render(_hdc);
}

void CShield::Release(void)
{
}
