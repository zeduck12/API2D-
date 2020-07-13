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
		if (iRandNum > 5)  // 달리다가 2분의 1 확률로 Idle
			SetBossState(_pBoss, IdleState::Get_Instance());
		else			   // 달리다가 2분의 1 확률로 다시 Run
			SetBossState(_pBoss, RunState::Get_Instance());
	}
	else
	{
		// 단순하게 정해진 보스의 범위내에서 돌아다님
		if (_pBoss->GetX() < 200.f)
			_pBoss->SetSpeed(_pBoss->GetSpeed() * -1.f);
		else if (_pBoss->GetX() > 800.f)
			_pBoss->SetSpeed(_pBoss->GetSpeed() * -1.f);

		_pBoss->SetX(_pBoss->GetX() + _pBoss->GetSpeed());
	}
}

void IdleState::OnLoaded(CBoss* _pBoss)
{
	// 멤버변수 초기화.
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
			SetBossState(_pBoss, TrackingState::Get_Instance()); // 나중에 트랙킹.
	}
}

void AttackState::OnLoaded(CBoss* _pBoss)
{

}

void AttackState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	
	// 플레이어에게 공격데미지
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
	// 현재 보스가 넘어진 상태에서 공격을 받았을때 드어옴
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
	// 목적지
	float fEndPosX = pPlayer->GetX();
	// 방향 설정.
	_pBoss->CheckDirection();

	// 목적지까지 거리
	float fDeltaX = fEndPosX - _pBoss->GetX();
	float fDistance = sqrtf(fDeltaX * fDeltaX);

	// 이동속도
	float fSpeed = fDeltaX / fDistance * _pBoss->GetSpeed();
	// 움직임.
	_pBoss->SetX(_pBoss->GetX() + fSpeed);


	if (pPlayer->GetX() - 10.f < _pBoss->GetX() &&
		pPlayer->GetX() + 10.f > _pBoss->GetX())
	{
		// 플레이어 근처에 보스가 도착했다면
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
		// 웨이브를 생성해서 플레이어 방향으로 날려준다.
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
	// 몇초에 한번씩 떨어지게 하기.
	// 자신을 기준으로 하늘에서 랜덤한 위치에 동그란 유성들 떨어지게 하기.
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
	// 양방향으로 도끼 휘두르기.
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
	// 넘어진 상태에 들어오면 공격만 받음
	// 일정시간 넘어가면 다시 돌아감 
	m_fFallAccumulateTime += CTimeManager::Get_Instance()->GetElapsedTime();
	if (m_fFallAccumulateTime > m_fFallCoolTime)
	{
		m_fFallAccumulateTime = 0.f;
		// 만약에 맞았다면 어택드 상태로 넘어가서 맞은 카운트 늘려주고 데미지 받고
		// 맞은 애니메이션 넣어주기.
		// 현재 보스는 넘어졌을때만 어택드 상태가 됨.
		
	}
}

void JumpState::OnLoaded(CBoss* _pBoss)
{
}

void JumpState::Update(CBoss* _pBoss, float _fDeltaTime)
{
	// 두번 점프가 끝.
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
		//이떄 점프
		_pBoss->SetIsJump(true);
		_pBoss->ActiveGravity();
	}
}
