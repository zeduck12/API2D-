#include "framework.h"
#include "CMonster.h"
#include "CGameScene.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CSubBullet.h"
#include "CAttackPattern.h"

CMonster::CMonster(CGameScene& _rGameScene, float _fX, float _fY, size_t _iWidth, size_t _iHeight, float _fHp, MONSTER::E_PATTERN _ePattern/* = MONSTER::CRAWL*/)
	:
	CObj(_rGameScene, 0.f, 0.f, _iWidth, _iHeight, 0.f, 0.f),
	m_fHp(_fHp),
	m_eMonsterPattern(_ePattern)
{
	m_fX = _fX;
	m_fY = _fY;
	m_fMaxHp = m_fHp;
	m_fSpeed = cfMonsterSpeed;

	m_pAttackPattern = new CAttackPattern(_rGameScene, this, m_eMonsterPattern);
}

CMonster::CMonster(CGameScene& _rGameScene, size_t _iWidth, size_t _iHeight, float _fHp, MONSTER::E_PATTERN _ePattern)
	:
	CObj(_rGameScene, 0.f, 0.f, _iWidth, _iHeight, 0.f,0.f),
	m_fHp(_fHp),
	m_eMonsterPattern(_ePattern)
{
	m_fX = GetNumberMinBetweenMax(0.f, float(WINCX));
	m_fY = GetNumberMinBetweenMax(0.f, float(WINCY));
	m_fMaxHp = m_fHp;
	m_fSpeed = cfMonsterSpeed;

	m_pAttackPattern = new CAttackPattern(_rGameScene, this, m_eMonsterPattern);
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Ready(void)
{
}

int CMonster::Update(float _fDeltaTime)
{
	SetDirection(); // 플레이어 기준으로 몬스터 방향검사.
	ActiveGravity();
	DO_IF_IS_VALID_OBJ(m_pAttackPattern) { m_pAttackPattern->Update(); }

	return 0;
}

void CMonster::LateUpdate(void)
{
	// 중력체크
	if (m_fY > WINCY - 100.f - 25.f)
	{
		m_fGravity = 0.f;
		m_fY = WINCY - 100.f - 25.f; // -25.f 지면 위에다 플레이어 놓기 위해서 해준거.
	}


	// 현재 몬스터가 죽었는지 체크.
	if (IsDied())
		SetValid(false);
}

void CMonster::Render(const HDC& _hdc)
{
	CObj::Render(_hdc);

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

void CMonster::Release(void)
{
	DeleteSafe(m_pAttackPattern);
}

void CMonster::Knockback(PLAYER::E_DIRECTION _eDir)
{
	// 보스들은 넉백안됨.
	if (m_eMonsterPattern == MONSTER::JUNIOR_BOSS || m_eMonsterPattern == MONSTER::LAST_BOSS)
		return;

	m_bIsKnockBack = true;
	if (_eDir == PLAYER::LEFT)
		m_fX -= 100.f;
	else if (_eDir == PLAYER::RIGHT)
		m_fX += 100.f;
}

void CMonster::ActiveGravity()
{
	if (m_eMonsterPattern == MONSTER::FLY)
		return;

	m_fGravity += GRAVITY;
	m_fY += m_fGravity;
}

void CMonster::SetDirection(void)
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

