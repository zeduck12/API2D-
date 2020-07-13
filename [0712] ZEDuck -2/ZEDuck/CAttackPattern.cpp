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
	// ���� ���� ���� ���͸� ��ġ������ ������ ����.
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
	// �÷��̾� ����
	float temp = atan2f(GetGameScene().GetPlayer()->GetY() - m_fY, GetGameScene().GetPlayer()->GetX() - m_fX);

	m_pOwner->SetX(m_pOwner->GetX() + m_fSpeed * cosf(temp));
	m_pOwner->SetY(m_pOwner->GetY() + m_fSpeed * sinf(temp));
}

void CAttackPattern::Patrol(void)
{
	// X�� ���� ���ص�
	// �ּ� : 300.f ,�ִ� : 900.f
	// y�� ������ ���ص�
	// �ּ� : 400.f ,�ִ� : 600.f
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
		// ���ڸ��� ���ư��� ���� �ִ��ڸ���
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
		// �÷��̾�� ������.
		if (CheckAttackRange() == true)
		{
			// �÷��̾� ���ݹ����� ��� �ϳ� ����.
			if (pPlayer->GetLifeNum() > 0) 
				pPlayer->SetLifeNum(pPlayer->GetLifeNum() - 1);
			else 
				pPlayer->SetValid(false);
			return;	// �÷��̾ ���� �����̹Ƿ� �� �̻��� ������ �������� �ʴ´�.
		}
	}
	
}

bool CAttackPattern::DetectPlayer(void)
{
	CObj* pPlayer = GetGameScene().GetPlayer();
	DO_IF_IS_VALID_OBJ(pPlayer)
	{
		// �������� 
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
	// ���̺긦 �����ؼ� �÷��̾� �������� �����ش�.
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
		// ���� ���� �����ʰ��ݸ� �˻�
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

// �ܼ��ϰ� ���ٴϴ� ���� ����. (����üũ x)
void CAttackPattern::StartCrawlPattern(void)
{
	if (TO_MONSTER(m_pOwner)->GetIsKnockBack() == true)
	{
		// �˹� ���¶�� ��� ���߱�.
		// ���ݼӵ� ������
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

// �޷����� ������ ���� ���ǵ� 4.5 ����
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
		// �÷��̾ ���� ���ݹ������� ������
		// �÷��̾ �Ѿư��� ������. 
		// �ٵ� �޷����� �����Ÿ��� �����̰� ������ �ٽ� ������.
		if (m_fAttackCoolTime == 130.f)
		{
			m_iAttackPatternDelay++;
			if (m_iAttackPatternDelay > 70)
			{
				m_iAttackPatternDelay = 0;
				m_fAttackCoolTime = 0.f;
				// �������� ���⺤��
				DO_IF_IS_VALID_OBJ(GetGameScene().GetPlayer())
					m_fVec = GetGameScene().GetPlayer()->GetX() - m_pOwner->GetX();
			}
		}
		else
		{
			m_fAttackCoolTime += 2.f;
			// �÷��̾��� ������ �����ֱ⿡ �ѹ��� �޾ƿ���.
			if (m_fVec != 0)
			{		
				float fDst = sqrtf(m_fVec * m_fVec);
				m_pOwner->SetX(m_pOwner->GetX() + /*m_fSpeed*/5.f * m_fVec / fDst);
			}

		}
	}
}

// ���ǵ� 4,5
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
		// ������������ �÷��̾ �ִ��� �켱üũ.
		// ���࿡ ������������ �÷��̾ �ִٸ� ����.
		if (m_fAttackCoolTime == 130.f)
		{
			m_iAttackPatternDelay++;
			if (m_iAttackPatternDelay > 70)
			{
				m_iAttackPatternDelay = 0;
				m_fAttackCoolTime = 0.f;
				// �������� ���⺤��
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

				// �����ѹ��� �ٰ� ����ó��.
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
		// ���Ͱ� �÷��̾ �����ϴ� �������� ������ �÷��̾� �ѱ�
		// �� ������ ������ �ε����°�.
		if (DetectPlayer() == true)
			Tracking();
		else
			Patrol();
	}
}

void CAttackPattern::StartJuniorBossPattern(void)
{
	// ������������ �÷��̾ �ִ��� �켱üũ.
	// ���࿡ ������������ �÷��̾ �ִٸ� ����.

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
			// ���⼭ ������ ���� ������ ��������.
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

	// ������ �ǰ� �����Ϸ� �������� ���� ����߸� �������� �⺻ ���̺� ���ݰ� ��ġ �ֵθ��� 
	// �׸��� ��������.
	if (TO_MONSTER(m_pOwner)->GetHp() <= TO_MONSTER(m_pOwner)->GetMaxHp() * 0.5f)
	{
		// ������ 2
	}
	else
	{
		// ������ 1
	}

	// �⺻ ��ġ �ֵθ���.
	Attack();
	// ��ġ �ֵθ��� ���̺� �߻�
	Attack(); WaveAttack();
	// ��ġ �¿�� �ֵѸ��鼭 ������ ���� ����߸�
	Attack(); // ��������.
	// �����ϸ鼭 ����.
	//Run()
}