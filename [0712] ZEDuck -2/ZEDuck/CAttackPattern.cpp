#include "framework.h"
#include "CAttackPattern.h"
#include "CGameScene.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CBullet.h"

CAttackPattern::CAttackPattern(CGameScene& _rGameWorld, CObj* _pOwner, MONSTER::E_PATTERN _ePattern)
	:
	m_pOwner(nullptr),
	m_eMonsterPattern(_ePattern),
	CObj(_rGameWorld, 0.f, 0.f, 0, 0)
{
	// 현재 나를 붙인 몬스터를 위치정보를 가지고 있음.
	if (_pOwner)
	{
		m_pOwner = _pOwner;
		SetX(m_pOwner->GetX());
		SetY(m_pOwner->GetY());
		m_fSpeed = m_pOwner->GetSpeed();
		m_fSpeedX = m_pOwner->GetSpeed();
		m_fSpeedY = m_pOwner->GetSpeed();
	}

}

CAttackPattern::~CAttackPattern()
{
	Release();
}

int CAttackPattern::Update(float _fDeltaTime)
{
	if (m_pOwner) 
	{
		SetX(m_pOwner->GetX());
		SetY(m_pOwner->GetY());
	}

	switch (m_eMonsterPattern)
	{
	case MONSTER::CRAWL:
		StartCrawlPattern();
		break;
	case MONSTER::CRUSH:
		StartRunPattern();
		break;
	case MONSTER::JUMP:
		StartJumpPattern();
		break;
	case MONSTER::FLY:
		StartFlyPattern();
		break;
	case MONSTER::JUNIOR_BOSS:
		StartJuniorBossPattern();
		break;
	case MONSTER::LAST_BOSS:
		StartLastBossPattern();
		break;
	default:
		break;
	}


	return 0;
}

void CAttackPattern::LateUpdate(void)
{
}

void CAttackPattern::Release(void)
{
	m_pOwner = nullptr;
}


void CAttackPattern::Jump()
{
	m_fJumpPower = 20.f;
	m_fJumpAngle = 40.f;
	m_pOwner->SetY(m_pOwner->GetY() - m_fJumpPower);
}

void CAttackPattern::MiniJump()
{
	m_fJumpPower = 20.f;
	m_fJumpAngle = 40.f;
	m_pOwner->SetY(m_pOwner->GetY() - m_fJumpPower);
	m_pOwner->SetX(m_pOwner->GetX() + 3.f);
}

void CAttackPattern::Tracking(void)
{
	// 플레이어 추적
	float temp = atan2f(GetGameScene().GetPlayer()->GetY() - m_fY, GetGameScene().GetPlayer()->GetX() - m_fX);

	m_pOwner->SetX(m_pOwner->GetX() + m_fSpeed * cosf(temp));
	m_pOwner->SetY(m_pOwner->GetY() + m_fSpeed * sinf(temp));
}

void CAttackPattern::Patrol(void)
{
	// X값 범위 정해둠
	// 최소 : 300.f ,최대 : 900.f
	// y값 범위도 정해둠
	// 최소 : 400.f ,최대 : 600.f
	if (m_pOwner->GetX() > 590.f && m_pOwner->GetX() < 610.f && m_pOwner->GetY() > 490.f && m_pOwner->GetY() < 510.f)
		m_bIsReturnToHome = true;

	if (IsOutOfRange() == false && m_bIsReturnToHome == true)
	{
		if (m_pOwner->GetX() < 300.f)
			m_fSpeedX *= -1.f;
		else if (m_pOwner->GetX() > 900.f)
			m_fSpeedX *= -1.f;


		if (m_pOwner->GetY() < 400.f)
			m_fSpeedY *= -1.f;
		else if (m_pOwner->GetY() > 600.f)
			m_fSpeedY *= -1.f;

		m_pOwner->SetX(m_pOwner->GetX() + m_fSpeedX);
		m_pOwner->SetY(m_pOwner->GetY() + m_fSpeedY);
	}
	else
	{
		// 제자리로 돌아가기 원래 있던자리로
		float temp = atan2f(WINCY - 500.f - m_pOwner->GetY(), 600.f - m_pOwner->GetX());

		m_pOwner->SetX(m_pOwner->GetX() + m_fSpeed * cosf(temp));
		m_pOwner->SetY(m_pOwner->GetY() + m_fSpeed * sinf(temp));
	}


}

bool CAttackPattern::IsOutOfRange(void)
{
	if (m_pOwner->GetX() < 290.f) { m_bIsReturnToHome = false; return true; }
	if (m_pOwner->GetX() > 910.f) {	m_bIsReturnToHome = false; return true; }
	if (m_pOwner->GetY() < 390.f) { m_bIsReturnToHome = false; return true; }
	if (m_pOwner->GetY() > 610.f) { m_bIsReturnToHome = false; return true; }

	return false;
}

void CAttackPattern::Attack(void)
{
	TO_MONSTER(m_pOwner)->SetMonsterState(MONSTER::ATTACK);
	CPlayer* pPlayer = TO_PLAYER(GetGameScene().GetPlayer());
	DO_IF_IS_VALID_OBJ(pPlayer)
	{
		// 플레이어에게 데미지.
		if (CheckAttackRange() == true)
		{
			// 플레이어 공격받으면 목숨 하나 깍임.
			if (pPlayer->GetLifeNum() > 0) 
				pPlayer->SetLifeNum(pPlayer->GetLifeNum() - 1);
			else 
				pPlayer->SetValid(false);
			return;	// 플레이어가 죽은 상태이므로 더 이상의 연산을 수행하지 않는다.
		}
	}
	
}

bool CAttackPattern::DetectPlayer(void)
{
	CObj* pPlayer = GetGameScene().GetPlayer();
	DO_IF_IS_VALID_OBJ(pPlayer)
	{
		// 범위내에 
		if (pPlayer->GetX() > m_pOwner->GetX() - cfMonsterDetectRange &&
			pPlayer->GetX() < m_pOwner->GetX() + cfMonsterDetectRange &&
			pPlayer->GetY() > m_pOwner->GetY() - cfMonsterDetectRange &&
			pPlayer->GetY() < m_pOwner->GetY() + cfMonsterDetectRange)
		{
			return true;
		}
	}

	return false;
}

void CAttackPattern::WaveAttack(void)
{
	// 웨이브를 생성해서 플레이어 방향으로 날려준다.
	CObj* pBullet = new CBullet(
		GetGameScene(), m_pOwner,
		m_pOwner->GetX(), WINCY - 100.f,
		GetGameScene().GetPlayer()->GetX(), WINCY - 100.f, 100, 30);
	pBullet->Ready();
	GetGameScene().GetBullets().emplace_back(pBullet);
}

bool CAttackPattern::CheckAttackRange(void)
{
	DO_IF_IS_VALID_OBJ(GetGameScene().GetPlayer())
	{
		// 현재 왼쪽 오른쪽공격만 검사
		if (GetGameScene().GetPlayer()->GetRight() > this->GetX() - cfMonsterAttackRange &&
			GetGameScene().GetPlayer()->GetRight() < this->GetX() + cfMonsterAttackRange &&
			GetGameScene().GetPlayer()->GetY() < this->GetY() + 50.f && 
			GetGameScene().GetPlayer()->GetY() > this->GetY() - 50.f)
			return true;


		if (GetGameScene().GetPlayer()->GetLeft() < this->GetX() + cfMonsterAttackRange &&
			GetGameScene().GetPlayer()->GetLeft() > this->GetX() - cfMonsterAttackRange &&
			GetGameScene().GetPlayer()->GetY() < this->GetY() + 50.f &&
			GetGameScene().GetPlayer()->GetY() > this->GetY() - 50.f)
			return true;
	}

	return false;
}

// 단순하게 기어다니는 몬스터 패턴. (범위체크 x)
void CAttackPattern::StartCrawlPattern(void)
{
	if (TO_MONSTER(m_pOwner)->GetIsKnockBack() == true)
	{
		// 넉백 상태라면 잠시 멈추기.
		// 공격속도 딜레이
		m_iAttackTimeDelay++;
		if (m_iAttackTimeDelay > 25)
		{
			m_iAttackTimeDelay = 0;
			TO_MONSTER(m_pOwner)->SetIsKnockBack(false);
		}
	}
	else
	{
		if (m_pOwner->GetX() < 200.f)
			m_fSpeed *= -1.f;
		else if (m_pOwner->GetX() > 800.f)
			m_fSpeed *= -1.f;

		m_pOwner->SetX(m_pOwner->GetX() + m_fSpeed);
	}
}

// 달려오는 패턴의 몬스터 스피드 4.5 적당
void CAttackPattern::StartRunPattern(void)
{
	if (DetectPlayer() == false)
		return;

	if (TO_MONSTER(m_pOwner)->GetIsKnockBack() == true)
	{
		m_iAttackTimeDelay++;
		if (m_iAttackTimeDelay > 25)
		{
			m_iAttackTimeDelay = 0;
			TO_MONSTER(m_pOwner)->SetIsKnockBack(false);
		}
	}
	else
	{
		// 플레이어가 몬스터 공격범위내에 들어오면
		// 플레이어를 쫓아가서 공격함. 
		// 근데 달려갈때 일정거리만 움직이고 쉬었다 다시 움직임.
		if (m_fAttackCoolTime == 130.f)
		{
			m_iAttackPatternDelay++;
			if (m_iAttackPatternDelay > 70)
			{
				m_iAttackPatternDelay = 0;
				m_fAttackCoolTime = 0.f;
				// 직선상의 방향벡터
				DO_IF_IS_VALID_OBJ(GetGameScene().GetPlayer())
					m_fVec = GetGameScene().GetPlayer()->GetX() - m_pOwner->GetX();
			}
		}
		else
		{
			m_fAttackCoolTime += 2.f;
			// 플레이어의 정보를 일정주기에 한번씩 받아오기.
			if (m_fVec != 0)
			{		
				float fDst = sqrtf(m_fVec * m_fVec);
				m_pOwner->SetX(m_pOwner->GetX() + /*m_fSpeed*/5.f * m_fVec / fDst);
			}

		}
	}
}

// 스피드 4,5
void CAttackPattern::StartJumpPattern(void)
{
	if (DetectPlayer() == false)
		return;

	if (TO_MONSTER(m_pOwner)->GetIsKnockBack() == true)
	{
		m_iAttackTimeDelay++;
		if (m_iAttackTimeDelay > 25)
		{
			m_iAttackTimeDelay = 0;
			TO_MONSTER(m_pOwner)->SetIsKnockBack(false);
		}
	}
	else
	{
		// 일정범위내에 플레이어가 있는지 우선체크.
		// 만약에 일정범위내에 플레이어가 있다면 공격.
		if (m_fAttackCoolTime == 130.f)
		{
			m_iAttackPatternDelay++;
			if (m_iAttackPatternDelay > 70)
			{
				m_iAttackPatternDelay = 0;
				m_fAttackCoolTime = 0.f;
				// 직선상의 방향벡터
				m_bIsJump = false;
				DO_IF_IS_VALID_OBJ(GetGameScene().GetPlayer())				
					m_fVec = GetGameScene().GetPlayer()->GetX() - m_pOwner->GetX();
				

			}
		}
		else
		{
			m_fAttackCoolTime += 2.f;
			if (m_fVec != 0 )
			{

				float fDst = sqrtf(m_fVec * m_fVec);
				if (m_bIsJump == false)
				{
					m_pOwner->SetX(m_pOwner->GetX() + m_fSpeed * m_fVec / fDst);
					Jump();
				}

				// 점프한번만 뛰게 예외처리.
				if (m_pOwner->GetY() == WINCY - 100.f - 25.f)
				{
					m_bIsJump = true;
					if (CheckAttackRange() == true)
						Attack();
				}
			
			}

		}
	}
}

//cfMonsterSpeed = 1.5f
//cfMonsterDetectRange = 350.f;
void CAttackPattern::StartFlyPattern(void)
{
	if (TO_MONSTER(m_pOwner)->GetIsKnockBack() == true)
	{
		m_iAttackTimeDelay++;
		if (m_iAttackTimeDelay > 25)
		{
			m_iAttackTimeDelay = 0;
			TO_MONSTER(m_pOwner)->SetIsKnockBack(false);
		}
	}
	else
	{
		// 몬스터가 플레이어를 감지하는 범위내에 있으면 플레이어 쫓기
		// 이 몬스터의 공격은 부딪히는거.
		if (DetectPlayer() == true)
			Tracking();
		else
			Patrol();
	}
}

void CAttackPattern::StartJuniorBossPattern(void)
{
	// 일정범위내에 플레이어가 있는지 우선체크.
	// 만약에 일정범위내에 플레이어가 있다면 공격.

	CObj* pPlayer = GetGameScene().GetPlayer();
	DO_IF_IS_VALID_OBJ(pPlayer)
	{
		if (m_fAttackCoolTime == 130.f)
		{
			m_iAttackPatternDelay++;
			if (m_iAttackPatternDelay > 100)
			{
				m_iAttackPatternDelay = 0;
				m_fAttackCoolTime = 0.f;
				m_bIsJump = false;
				m_bIsAttack = false;
				DO_IF_IS_VALID_OBJ(GetGameScene().GetPlayer())
					m_fVec = GetGameScene().GetPlayer()->GetX() - m_pOwner->GetX();
			}
		}
		else
		{
			m_fAttackCoolTime += 2.f;
			// 여기서 범위에 따른 공격이 나가야함.
			if (GetGameScene().GetPlayer()->GetX() > m_pOwner->GetX() - 100.f &&
				GetGameScene().GetPlayer()->GetX() < m_pOwner->GetX() + 100.f)
			{
				if (m_bIsAttack == true)
					return;

				m_bIsAttack = true;
				if (CheckAttackRange() == true)
					Attack();
			}
			else if (pPlayer->GetX() < m_pOwner->GetX() - 100.f && pPlayer->GetX() > m_pOwner->GetX() - 200.f
				|| pPlayer->GetX() > m_pOwner->GetX() + 100.f && pPlayer->GetX() < m_pOwner->GetX() + 200.f)
			{
				if (m_fVec != 0)
				{
					float fDst = sqrtf(m_fVec * m_fVec);
					if (m_bIsJump == false)
					{
						m_pOwner->SetX(m_pOwner->GetX() + m_fSpeed * m_fVec / fDst);
						MiniJump();
					}

					if (m_pOwner->GetY() == WINCY - 100.f - 25.f)
					{
						m_bIsJump = true;
						Attack();
						WaveAttack();
					}
				}

			}
		}
	}
}


void CAttackPattern::StartLastBossPattern(void)
{

	// 보스가 피가 반이하로 떨어지면 유성 떨어뜨림 그전에는 기본 웨이브 공격과 망치 휘두르기 
	// 그리고 돌진공격.
	if (TO_MONSTER(m_pOwner)->GetHp() <= TO_MONSTER(m_pOwner)->GetMaxHp() * 0.5f)
	{
		// 페이지 2
	}
	else
	{
		// 페이지 1
	}

	// 기본 망치 휘두르기.
	Attack();
	// 망치 휘두르고 웨이브 발사
	Attack(); WaveAttack();
	// 망치 좌우로 휘둘르면서 위에서 유성 떨어뜨림
	Attack(); // 유성생성.
	// 점프하면서 돌진.
	//Run()
}