#include "framework.h"
#include "CBossState.h"
#include "CGameScene.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CMeteor.h"
#include"CTimeManager.h"

RunState* RunState::instance;
IdleState* IdleState::instance;
AttackState* AttackState::instance;
AttackedState* AttackedState::instance;
TrackingState* TrackingState::instance;
WaveAttackState* WaveAttackState::instance;
MeteorAttackState* MeteorAttackState::instance;
DoubleSideAttackState* DoubleSideAttackState::instance;
FallState* FallState::instance;
JumpState* JumpState::instance;

void RunState::OnLoaded(CBoss* _pBoss)
{
}

void RunState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	fStateDelay = 1000.f;
	fAccumulateTime += 1/*_fDeltaTime*/;
	if (fStateDelay < fAccumulateTime)
	{
		fAccumulateTime = 0.f;

		int iRandNum = rand() % 10 + 1;
		if (iRandNum > 5)  // �޸��ٰ� 2���� 1 Ȯ���� Idle
			SetBossState(_pBoss, IdleState::Get_Instance());
		else			   // �޸��ٰ� 2���� 1 Ȯ���� �ٽ� Run
			SetBossState(_pBoss, RunState::Get_Instance());
	}
	else
	{
		// �ܼ��ϰ� ������ ������ ���������� ���ƴٴ�
		if (_pBoss->GetX() < 200.f)
			_pBoss->SetSpeed(_pBoss->GetSpeed() * -1.f);
		else if (_pBoss->GetX() > 800.f)
			_pBoss->SetSpeed(_pBoss->GetSpeed() * -1.f);

		_pBoss->SetX(_pBoss->GetX() + _pBoss->GetSpeed());
	}
}

void IdleState::OnLoaded(CBoss* _pBoss)
{
	// ������� �ʱ�ȭ.
}

void IdleState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	fStateDelay = 100.f;
	fAccumulateTime += 1/*_fDeltaTime*/;
	if (fStateDelay < fAccumulateTime)
	{
		fAccumulateTime = 0.f;

		if (_pBoss->CheckAttackRange() == true)
			SetBossState(_pBoss, AttackState::Get_Instance());
		else if(_pBoss->CheckAttackRange() == false)
			SetBossState(_pBoss, TrackingState::Get_Instance()); // ���߿� Ʈ��ŷ.
	}
}

void AttackState::OnLoaded(CBoss* _pBoss)
{

}

void AttackState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	
	// �÷��̾�� ���ݵ�����
	_pBoss->SetBossState(MONSTER::ATTACK);
	CPlayer* pPlayer = TO_PLAYER(_pBoss->GetGameScene().GetPlayer());
	DO_IF_IS_VALID_OBJ(pPlayer)
	{
		if (pPlayer->GetLifeNum() > 0)
			pPlayer->SetLifeNum(pPlayer->GetLifeNum() - 1);
		else
			pPlayer->SetValid(false);

		int iRandNum = rand() % 3 + 1;

		if (iRandNum == 1)
			SetBossState(_pBoss, IdleState::Get_Instance());
		else if (iRandNum == 2)
			SetBossState(_pBoss, TrackingState::Get_Instance());
	}
}

void AttackedState::OnLoaded(CBoss* _pBoss)
{
}

void AttackedState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	// ���� ������ �Ѿ��� ���¿��� ������ �޾����� ����
	_pBoss->SetAttackedCount(_pBoss->GetAttackedCount() + 1);
	_pBoss->TakeDamage(TO_PLAYER(_pBoss->GetGameScene().GetPlayer())->GetDamage());
	SetBossState(_pBoss, FallState::Get_Instance());
}

void TrackingState::OnLoaded(CBoss* _pBoss)
{
}

void TrackingState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	CPlayer* pPlayer = TO_PLAYER(_pBoss->GetGameScene().GetPlayer());
	// ������
	float fEndPosX = pPlayer->GetX();
	// ���� ����.
	_pBoss->CheckDirection();

	// ���������� �Ÿ�
	float fDeltaX = fEndPosX - _pBoss->GetX();
	float fDistance = sqrtf(fDeltaX * fDeltaX);

	// �̵��ӵ�
	float fSpeed = fDeltaX / fDistance * _pBoss->GetSpeed();
	// ������.
	_pBoss->SetX(_pBoss->GetX() + fSpeed);


	if (pPlayer->GetX() - 10.f < _pBoss->GetX() &&
		pPlayer->GetX() + 10.f > _pBoss->GetX())
	{
		// �÷��̾� ��ó�� ������ �����ߴٸ�
		SetBossState(_pBoss, AttackState::Get_Instance());
	}
	else
		SetBossState(_pBoss, TrackingState::Get_Instance());

}

void WaveAttackState::OnLoaded(CBoss* _pBoss)
{
}

void WaveAttackState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	m_fWaveAccumulateTime += CTimeManager::Get_Instance()->GetElapsedTime();
	if (m_fWaveAccumulateTime > m_fWaveCoolTime)
	{
		m_fWaveAccumulateTime = 0.f;
		// ���̺긦 �����ؼ� �÷��̾� �������� �����ش�.
		CObj* pBullet = new CBullet(
			_pBoss->GetGameScene(), _pBoss,
			_pBoss->GetX(), WINCY - 100.f,
			_pBoss->GetGameScene().GetPlayer()->GetX(), WINCY - 100.f, 200, 100);
		pBullet->Ready();
		_pBoss->GetGameScene().GetBullets().emplace_back(pBullet);
	}
}


void MeteorAttackState::OnLoaded(CBoss* _pBoss)
{
}

void MeteorAttackState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	// ���ʿ� �ѹ��� �������� �ϱ�.
	// �ڽ��� �������� �ϴÿ��� ������ ��ġ�� ���׶� ������ �������� �ϱ�.
	m_fMeteorAccumulateTime += CTimeManager::Get_Instance()->GetElapsedTime();
	if (m_fMeteorAccumulateTime > m_fMeteorCoolTime)
	{
		m_fMeteorAccumulateTime = 0.f;
		float fStartX = GetNumberMinBetweenMax(_pBoss->GetX() - 300.f, _pBoss->GetX() + 300.f);
		float fStartY = GetNumberMinBetweenMax(100.f, 300.f);

		CObj* pMeteor = new CMeteor(
			_pBoss->GetGameScene(), _pBoss,
			fStartX, fStartY,
			fStartX, WINCY - 100.f
		);
		pMeteor->Ready();
		_pBoss->GetGameScene().GetBullets().emplace_back(pMeteor);
	}
}

void DoubleSideAttackState::OnLoaded(CBoss* _pBoss)
{
}

void DoubleSideAttackState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	// ��������� ���� �ֵθ���.
	_pBoss->SetBossState(MONSTER::ATTACK);
	m_fAttackAccumulateTime += CTimeManager::Get_Instance()->GetElapsedTime();
	if (m_fAttackAccumulateTime > m_fAttackCoolTime)
	{
		m_fAttackAccumulateTime = 0.f;
		m_iAttackCount++;
		if (m_iAttackCount == 1)
			_pBoss->SetDirection(MONSTER::LEFT);
		else if (m_iAttackCount == 2)
			_pBoss->SetDirection(MONSTER::RIGHT);
		else if (m_iAttackCount == 3)
			_pBoss->SetDirection(MONSTER::LEFT);
		else
		{
			m_iAttackCount = 0;
			_pBoss->SetDirection(MONSTER::RIGHT);
		}
	}
}

void FallState::OnLoaded(CBoss* _pBoss)
{
}

void FallState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	// �Ѿ��� ���¿� ������ ���ݸ� ����
	// �����ð� �Ѿ�� �ٽ� ���ư� 
	m_fFallAccumulateTime += CTimeManager::Get_Instance()->GetElapsedTime();
	if (m_fFallAccumulateTime > m_fFallCoolTime)
	{
		m_fFallAccumulateTime = 0.f;
		// ���࿡ �¾Ҵٸ� ���õ� ���·� �Ѿ�� ���� ī��Ʈ �÷��ְ� ������ �ް�
		// ���� �ִϸ��̼� �־��ֱ�.
		// ���� ������ �Ѿ��������� ���õ� ���°� ��.
		
	}
}

void JumpState::OnLoaded(CBoss* _pBoss)
{
}

void JumpState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	// �ι� ������ ��.
	if (_pBoss->GetJumpCount() == 3)
	{
		_pBoss->SetIsJump(false); 
		_pBoss->SetGravity(0.f);
		_pBoss->ReSetJumpCount();
		return;
	}

	m_fJumpAccumulateTime += CTimeManager::Get_Instance()->GetElapsedTime();
	if (m_fJumpAccumulateTime > m_fJumpCoolTime)
		m_fJumpAccumulateTime = 0.f;
	else
	{
		//�̋� ����
		_pBoss->SetIsJump(true);
		_pBoss->ActiveGravity();
	}
}
