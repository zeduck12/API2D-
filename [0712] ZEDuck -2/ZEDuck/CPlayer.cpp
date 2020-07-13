#include "framework.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CGameScene.h"
#include "CGunBarrel.h"
#include "CShield.h"
#include "CMonster.h"

CPlayer::CPlayer(CGameScene& _rGameScene)
	:
	CObj(_rGameScene, 0, 0, ciPlayerSize, ciPlayerSize, cfPlayerSpeed,0.f, Rectangle)
{
	m_fJumpPower = 40.f;
}

CPlayer::CPlayer(CGameScene& _rGameScene, float _fX, float _fY, size_t _iWidth, size_t _iHeight, float _fSpeed, float _fDegree)
	:
	CObj(_rGameScene, _fX, _fY, _iWidth, _iHeight, _fSpeed, _fDegree, Rectangle)
{
	m_fJumpPower = 40.f;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Ready(void)
{
	
}

int CPlayer::Update(float _fDeltaTime)
{
	// 이전 위치
	oldPoint.x = GetX();
	oldPoint.y = GetY();

	if (m_bIsPressDown == true)
	{
		m_bIsPressDown = false;
		m_iHeight *= 2.f;
	}

	InputKeyState();
	ActiveGravity();

	return 0;
}

void CPlayer::LateUpdate(void)
{
	// 나중에 몬스터가 던지는 투사체들 플레이어가 피격데미지 입는거등등 처리..

	if (m_fY > WINCY - 100.f - 25.f)
	{
		eState = PLAYER::IDLE;
		m_fGravity = 0.f;
		m_fJumpPower = 0.f;
		m_iJumpCount = 0;
		m_fY = WINCY - 100.f - 25.f; // -25.f 지면 위에다 플레이어 놓기 위해서 해준거.
	}
}

void CPlayer::Render(const HDC& _hdc)
{
	//CObj::Render(_hdc);
	// 플레이어 기준으로 움직이게 구현하기.
	Rectangle(_hdc, GetLeft() + (m_fX- oldPoint.x), GetTop() + (m_fY- oldPoint.y),
		GetRight() + (m_fX-oldPoint.x), GetBottom() + (m_fY-oldPoint.y));

	if (eState == PLAYER::ATTACK)
	{
		if (eDirection == PLAYER::LEFT)
			Rectangle(_hdc, GetX() - cfPlayerAttackRange, GetY() - 10.f, GetX(), GetY() + 10.f);
		if (eDirection == PLAYER::RIGHT)
			Rectangle(_hdc, GetX() + cfPlayerAttackRange, GetY() - 10.f, GetX(), GetY() + 10.f);

		// 공격이 모션까지 끝나면 가만히 서있는 상태로.
		eState = PLAYER::IDLE;
	}
}

void CPlayer::Release(void)
{
}

void CPlayer::InputKeyState()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		eDirection = PLAYER::LEFT;
		m_fX -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		eDirection = PLAYER::RIGHT;
		m_fX += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		eDirection = PLAYER::DOWN;
		m_bIsPressDown = true;
		m_fY += m_fSpeed;
		m_iHeight *= 0.5f;
	}

	if (GetAsyncKeyState(VK_UP) & 0x0001)
	{
		if (m_iJumpCount == 2)
			return;
		else if (m_iJumpCount == 1)
		{
			m_fGravity = 0.f;
		}
		else if (m_iJumpCount == 0)
		{
			eState = PLAYER::JUMP;
			m_fJumpPower = 40.f;
			m_fJumpAngle = 40.f;
			m_fGravity = 0.f;
		}

		m_iJumpCount++;
	}

	// 공격하기
	if (GetAsyncKeyState('A') & 0x8000)
	{
		eState = PLAYER::ATTACK;
		Attack();
	}
}

void CPlayer::ActiveGravity()
{
	m_fY -= sinf(TO_RADIAN(m_fJumpAngle)) * m_fJumpPower;
	m_fY += m_fGravity;
	m_fGravity += GRAVITY;
}

void CPlayer::ResetPlayerVariable(void)
{
	eState = PLAYER::IDLE;
	m_fGravity = 0.f;
	m_fJumpPower = 0.f;
	m_iJumpCount = 0;
}

// 플레이어 기준으로 일점범위 내에 몬스터가 있는지 체크하는 함수,
bool CPlayer::CheckAttackRange(CObj* pObj)
{
	// 현재 왼쪽 오른쪽공격만 검사
	if (eDirection == PLAYER::LEFT)
	{
		if (pObj->GetRight() > this->GetX() - cfPlayerAttackRange && pObj->GetRight() < this->GetX()
			&& pObj->GetY() < this->GetY() + 50.f && pObj->GetY() > this->GetY() - 50.f)	
			return true;
	}

	if (eDirection == PLAYER::RIGHT)
	{
		if (pObj->GetLeft() < this->GetX() + cfPlayerAttackRange && pObj->GetLeft() > this->GetX()
			&& pObj->GetY() < this->GetY() + 50.f && pObj->GetY() > this->GetY() - 50.f)
			return true;
	}

	return false;
}

// 몬스터리스트를 돌면서 현재 플레이어 공격범위에 있는지 체크 후 있다면 공격 !
void CPlayer::Attack()
{
	RECT rc = {};
	CMonster* pMonster = nullptr;
	for (auto& pObj : GetGameScene().GetMonsters())
	{
		DO_IF_IS_VALID_OBJ((pMonster = TO_MONSTER(pObj)))
		{
			// 몬스터에게 데미지.
			if (CheckAttackRange(pMonster))
			{
				pMonster->TakeDamage(cfPlayerDamage);
				pMonster->Knockback(eDirection); // 몬스터 넉백시켜주기.
			}
		}
	}
}


	


