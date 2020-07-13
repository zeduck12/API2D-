#include "framework.h"
#include "CGround.h"
#include "CGameScene.h"
#include "CPlayer.h"
#include "CBoss.h"
#include "CMonster.h"

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
	// 충돌체크 수정
	RECT rc = {};
	CPlayer* pPlayer = TO_PLAYER(GetGameScene().GetPlayer());
	RECT rcPlayer = pPlayer->GetRect();
	RECT rcGround = this->GetRect();
	if (IntersectRect(&rc,&rcPlayer,&rcGround))
	{
		// 플레이어와 그라운드가 충돌하면 충돌한 크기만큼의 렉트가 반환.
		// rc가 충돌한 크기의 렉트
		int iHorizontal = rc.right - rc.left;
		int iVertical = rc.bottom - rc.top;

		if (iHorizontal > iVertical)
		{
			// 플레이어 벽타기 못하게 막기, 
			// 만약에 벽타기를 가능하게 할려면 저것들을 조정하면 됨
			if (pPlayer->GetY() < this->GetY())
			{
				pPlayer->SetSpeed(cfPlayerSpeed);
				pPlayer->SetIsCollideCelling(false);
				pPlayer->ResetPlayerVariable();
				pPlayer->SetY(pPlayer->GetY() - iVertical);
			}
			else if(pPlayer->GetY() > this->GetY())
			{
				pPlayer->SetIsCollideCelling(true);
				pPlayer->ResetPlayerVariable();
				pPlayer->SetY(pPlayer->GetY() + iVertical);
			}
		}
		else
		{
			if (pPlayer->GetX() > this->GetX())
			{
				pPlayer->SetSpeed(0.f);
				pPlayer->SetX(pPlayer->GetX() + iHorizontal);
			}
			else if (pPlayer->GetX() < this->GetX())
			{
				pPlayer->SetSpeed(0.f);
				pPlayer->SetX(pPlayer->GetX() - iHorizontal);

			}

		}
	}

	CBoss* pBoss = TO_BOSS(GetGameScene().GetBoss());
	RECT rcBoss = pBoss->GetRect();
	if (IntersectRect(&rc, &rcBoss, &rcGround))
	{
		int iHorizontal = rc.right - rc.left;
		int iVertical = rc.bottom - rc.top;

		if (iHorizontal > iVertical)
		{
			if (pBoss->GetY() < this->GetY())
			{
				pBoss->SetGravity(0.f);
				pBoss->SetY(pBoss->GetY() - iVertical);
			}
			else if (pBoss->GetY() > this->GetY())
			{
				pBoss->SetGravity(0.f);
				pBoss->SetY(pBoss->GetY() + iVertical);
			}
		}
		else
		{
			if (pBoss->GetX() > this->GetX())
			{
				pBoss->SetGravity(0.f);
				pBoss->SetX(pBoss->GetX() + iHorizontal);
			}
			else if (pBoss->GetX() < this->GetX())
			{
				pBoss->SetGravity(0.f);
				pBoss->SetX(pBoss->GetX() - iHorizontal);
			}
		}
	}

	CMonster* pMonster = nullptr;
	RECT rcMonster = {};
	for (auto& pObj : GetGameScene().GetMonsters()) 
	{
		DO_IF_IS_VALID_OBJ((pMonster = TO_MONSTER(pObj))) 
		{
			rcMonster = pMonster->GetRect();
			if (IntersectRect(&rc, &rcMonster, &rcGround))
			{
				int iHorizontal = rc.right - rc.left;
				int iVertical = rc.bottom - rc.top;

				if (iHorizontal > iVertical)
				{
					if (pMonster->GetY() < this->GetY())
					{
						pMonster->SetGravity(0.f);
						pMonster->SetY(pMonster->GetY() - iVertical);
					}
					else if (pMonster->GetY() > this->GetY())
					{
						pMonster->SetGravity(0.f);
						pMonster->SetY(pMonster->GetY() + iVertical);
					}
				}
				else
				{
					if (pMonster->GetX() > this->GetX())
					{
						pMonster->SetGravity(0.f);
						pMonster->SetX(pMonster->GetX() + iHorizontal);
					}
					else if (pMonster->GetX() < this->GetX())
					{
						pMonster->SetGravity(0.f);
						pMonster->SetX(pMonster->GetX() - iHorizontal);
					}
				}
			}
			
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

