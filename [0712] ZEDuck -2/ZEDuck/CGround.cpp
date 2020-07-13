#include "framework.h"
#include "CGround.h"
#include "CGameScene.h"
#include "CPlayer.h"

CGround::CGround(CGameScene& _rGameScene, const GROUND_INFO& _rInfo)
	:
	CObj(_rGameScene, 0, 0),
	m_fSpeed(8.f),
	m_tInfo(_rInfo)
{
	m_fX = m_tInfo.fX;
	m_fY = m_tInfo.fY;
	m_iWidth = m_tInfo.iWidth;
	m_iHeight = m_tInfo.iHeight;
}

CGround::~CGround()
{
	Release();
}

void CGround::Ready()
{
}

int CGround::Update(float _fDeltaTime)
{
	return 0;
}

void CGround::LateUpdate(void)
{
	// 그라운드랑 플레이어가 충돌한다면 충돌한 만큼 플레이어를 위로 밀어내주기.
	RECT rcPlayer = GetGameScene().GetPlayer()->GetRect();
	RECT rcGround = this->GetRect();
	if (IntersectRect(rcPlayer, rcGround))
	{
		int iHorizontal = rcPlayer.right  - rcGround.left;
		int iVertical   = rcPlayer.bottom - rcGround.top;

		// 충돌하면 충돌한 만큼 플레이어를 위로 올려주기.
		if (iHorizontal > iVertical)
		{
			TO_PLAYER(GetGameScene().GetPlayer())->ResetPlayerVariable();
			GetGameScene().GetPlayer()->SetY(GetGameScene().GetPlayer()->GetY() - iVertical);
		}
		else
		{
			TO_PLAYER(GetGameScene().GetPlayer())->ResetPlayerVariable();
 			GetGameScene().GetPlayer()->SetX(GetGameScene().GetPlayer()->GetY() - iHorizontal);
		}
	}
	
}

void CGround::Render(const HDC& _hdc)
{
	Rectangle(_hdc, m_tInfo.fX - (m_tInfo.iWidth >> 1), m_tInfo.fY -(m_tInfo.iHeight >> 1),
		m_tInfo.fX + (m_tInfo.iWidth >> 1), m_tInfo.fY + (m_tInfo.iHeight >> 1));
}

void CGround::Release(void)
{
}
