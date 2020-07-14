#include "framework.h"
#include "CBoss.h"
#include "CBossState.h"
#include "CGameScene.h"
#include "CPlayer.h"

CBoss::CBoss(CGameScene& _rGameScene, float _fX, float _fY, size_t _iWidth, size_t _iHeight, float _fHp)
	:
	CObj(_rGameScene, 0.f, 0.f, _iWidth, _iHeight, 0.f, 0.f),
	m_fHp(_fHp)
{
	m_fX = _fX;
	m_fY = _fY;
	m_fMaxHp = m_fHp;
	m_fSpeed = cfMonsterSpeed;

	// 이미지
	m_iWidth = 256;
	m_iHeight = 256;
	//SetTexture("Boss", L"fly.bmp");

	// 상태 초기화
	m_eCurState = JumpState::Get_Instance();
	m_eCurState->OnLoaded(this);
}

CBoss::CBoss(CGameScene& _rGameScene, size_t _iWidth, size_t _iHeight, float _fHp)
	:
	CObj(_rGameScene, 0.f, 0.f, _iWidth, _iHeight, 0.f, 0.f),
	m_fHp(_fHp)
{
	m_fX = GetNumberMinBetweenMax(0.f, float(WINCX));
	m_fY = GetNumberMinBetweenMax(0.f, float(WINCY));
	m_fMaxHp = m_fHp;
	m_fSpeed = cfMonsterSpeed;

	// 상태 초기화
	m_eCurState = IdleState::Get_Instance();
}

CBoss::~CBoss()
{
	Release();
}

int CBoss::Update(float _fDeltaTime)
{
	// 중력은 항상받게.
	m_eCurState->Update(this, _fDeltaTime);
	ActiveGravity();
	return 0;
}

void CBoss::LateUpdate(void)
{
}

void CBoss::Render(const HDC& _hdc)
{
	CObj::Render(_hdc);
	//if (m_pTexture)
	//	BitBlt(_hdc, m_fX - (m_iWidth >> 1), m_fY - (m_iWidth >> 1), m_iWidth, m_iHeight, m_pTexture->GetDC(), 0, 0, SRCCOPY);

	if (m_eState == MONSTER::ATTACK)
	{
		if (m_eDirection == MONSTER::LEFT)
			Rectangle(_hdc, GetX() - cfMonsterAttackRange, GetY() - 10.f, GetX(), GetY() + 10.f);
		if (m_eDirection == MONSTER::RIGHT)
			Rectangle(_hdc, GetX() + cfMonsterAttackRange, GetY() - 10.f, GetX(), GetY() + 10.f);

		// 공격이 모션까지 끝나면 가만히 서있는 상태로.
		m_eState = MONSTER::IDLE;
	}
}

void CBoss::Release(void)
{
}

bool CBoss::DetectPlayer(void)
{
	CObj* pPlayer = GetGameScene().GetPlayer();
	DO_IF_IS_VALID_OBJ(pPlayer)
	{
		// 범위내에 
		if (pPlayer->GetX() > this->GetX() - cfBossDetectRange &&
			pPlayer->GetX() < this->GetX() + cfBossDetectRange &&
			pPlayer->GetY() > this->GetY() - cfBossDetectRange &&
			pPlayer->GetY() < this->GetY() + cfBossDetectRange)
		{
			return true;
		}
	}

	return false;
}

void CBoss::ActiveGravity(void)
{
	m_fGravity += /*GRAVITY*/ 0.2f;
	m_fY += m_fGravity;

	if (m_bIsJump == false)
		return;

	CPlayer* pPlayer = TO_PLAYER(this->GetGameScene().GetPlayer());
	DO_IF_IS_VALID_OBJ(pPlayer)
	{
		if (pPlayer->GetX() > this->GetX())
			m_fSpeed = 2.0f;
		else if (pPlayer->GetX() < this->GetX())
			m_fSpeed = -2.0f;
		else
			m_fSpeed = 0.f;
	}

	m_fY -= sinf(TO_RADIAN(40.f)) * 10.f;
	m_fX += m_fSpeed;

}

bool CBoss::CheckAttackRange(void)
{
	CObj* pPlayer = GetGameScene().GetPlayer();
	DO_IF_IS_VALID_OBJ(pPlayer)
	{
		if (pPlayer->GetX() > this->GetX() - 100.f && pPlayer->GetX() < this->GetX() + 100.f)
			return true;
		else
			return false;
	}

	return false;
}

void CBoss::SetState(CBossState* _pState)
{
	this->m_eCurState = _pState;
}

void CBoss::CheckDirection(void)
{
	CObj* pPlayer = GetGameScene().GetPlayer();
	DO_IF_IS_VALID_OBJ(pPlayer)
	{
		// 플레이어가 존재한다면
		if (pPlayer->GetX() < this->GetX())
			m_eDirection = MONSTER::LEFT;
		else
			m_eDirection = MONSTER::RIGHT;
	}
}
