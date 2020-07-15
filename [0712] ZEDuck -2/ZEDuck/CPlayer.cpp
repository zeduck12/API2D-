#include "framework.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CGameScene.h"
#include "CGunBarrel.h"
#include "CShield.h"
#include "CMonster.h"
#include "CBitmapManager.h"
#include "CAnimation.h"
#include "CTimeManager.h"
#include "CMyBitmap.h"

CPlayer::CPlayer(CGameScene& _rGameScene)
	:
	CObj(_rGameScene, 0, 0, ciPlayerSize, ciPlayerSize, cfPlayerSpeed,0.f, Rectangle)
{
	m_iWidth = 256;
	m_iHeight =128;
	m_fJumpPower = 40.f;
}

CPlayer::CPlayer(CGameScene& _rGameScene, float _fX, float _fY, size_t _iWidth, size_t _iHeight, float _fSpeed, float _fDegree)
	:
	CObj(_rGameScene, _fX, _fY, _iWidth, _iHeight, _fSpeed, _fDegree, Rectangle)
{
	m_iWidth = 256;
	m_iHeight = 128;
	m_fJumpPower = 40.f;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Ready(void)
{
	CBitmapManager::Get_Instance()->Insert_Texture_BmpMgr(L"Texture\\Test.bmp", L"Player");
	
	CAnimation* pAni = CreateAnimation("PlayerAnimation");
	AddAnimationClip("IdleLeft", ANIMATION::ATLAS, ANIMATION::LOOP, 0.8f, 1, 8 ,0,0, 1, 8 , 0.f, "PlayerIdle", L"Texture\\Test_Idle.bmp");
	AddAnimationClip("IdleRight", ANIMATION::ATLAS, ANIMATION::LOOP, 0.8f, 1, 8, 1, 0, 1, 8, 0.f, "PlayerIdle", L"Texture\\Test_Idle.bmp");
	AddAnimationClip("MoveLeft", ANIMATION::ATLAS, ANIMATION::ONCE_RETURN, 1.4f, 1, 7, 0, 0, 1, 7, 0.f, "PlayerMove", L"Texture\\Test_Move.bmp");
	AddAnimationClip("MoveRight", ANIMATION::ATLAS, ANIMATION::ONCE_RETURN, 1.4f, 1, 7, 1, 0, 1, 7, 0.f, "PlayerMove", L"Texture\\Test_Move.bmp");
	AddAnimationClip("JumpStartLeft", ANIMATION::ATLAS, ANIMATION::ONCE_RETURN, 0.5f, 1, 5, 0, 0, 1, 5, 0.f, "PlayerJumpStart", L"Texture\\Test_Jump_01.bmp");
	AddAnimationClip("JumpStartRight", ANIMATION::ATLAS, ANIMATION::ONCE_RETURN, 0.5f, 1, 5, 1, 0, 1, 5, 0.f, "PlayerJumpStart", L"Texture\\Test_Jump_01.bmp");
	AddAnimationClip("JumpReachHighLeft", ANIMATION::ATLAS, ANIMATION::ONCE_RETURN, 0.3f, 1, 3, 0, 0, 1, 3, 0.f, "PlayerJumpReachHigh", L"Texture\\Test_Jump_02.bmp");
	AddAnimationClip("JumpReachHighRight", ANIMATION::ATLAS, ANIMATION::ONCE_RETURN, 0.3f, 1, 3, 1, 0, 1, 3, 0.f, "PlayerJumpReachHigh", L"Texture\\Test_Jump_02.bmp");
	AddAnimationClip("JumpFallingLeft", ANIMATION::ATLAS, ANIMATION::ONCE_RETURN, 0.3f, 1, 3, 0, 0, 1, 3, 0.f, "PlayerJumpFalling", L"Texture\\Test_Jump_03.bmp");
	AddAnimationClip("JumpFallingRight", ANIMATION::ATLAS, ANIMATION::ONCE_RETURN, 0.3f, 1, 3, 1, 0, 1, 3, 0.f, "PlayerJumpFalling", L"Texture\\Test_Jump_03.bmp");
	AddAnimationClip("JumpLandingLeft", ANIMATION::ATLAS, ANIMATION::ONCE_RETURN, 0.3f, 1, 3, 0, 0, 1, 3, 0.f, "PlayerJumpLanding", L"Texture\\Test_Jump_04.bmp");
	AddAnimationClip("JumpLandingRigjt", ANIMATION::ATLAS, ANIMATION::ONCE_RETURN, 0.3f, 1, 3, 1, 0, 1, 3, 0.f, "PlayerJumpLanding", L"Texture\\Test_Jump_04.bmp");

	if (pAni) { pAni = nullptr; }
}

int CPlayer::Update(float _fDeltaTime)
{
	// 항상 업데이트에서 플레이어 state를 idle로 초기화해준다,
	eState = PLAYER::IDLE;
	if (m_pAnimation)
		m_pAnimation->Update(CTimeManager::Get_Instance()->GetElapsedTime());

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

}

void CPlayer::Render(const HDC& _hdc)
{
	if (eDirection == PLAYER::LEFT && eState == PLAYER::IDLE)
		m_pAnimation->ChangeClip("IdleLeft");
	if (eDirection == PLAYER::RIGHT && eState == PLAYER::IDLE)
		m_pAnimation->ChangeClip("IdleRight");
	if (eDirection == PLAYER::LEFT && eState == PLAYER::RUN)
		m_pAnimation->ChangeClip("MoveLeft");
	if (eDirection == PLAYER::RIGHT && eState == PLAYER::RUN)
		m_pAnimation->ChangeClip("MoveRight");
	if (eDirection == PLAYER::LEFT && eState == PLAYER::JUMP)
	{
		
	}


	POSITION tImagePos = {0,0};
	if (m_pAnimation)
	{
		ANIMATION_CLIP* pClip = m_pAnimation->GetCurrentClip();

		tImagePos.m_fX = pClip->iFrameX * m_iWidth;
		tImagePos.m_fY = pClip->iFrameY * m_iHeight;
	}

	GdiTransparentBlt(_hdc, GetLeft(), GetTop(),
		GetWidth(), GetHeight(),
		m_pMyBitmap->Get_MemDC(),
		tImagePos.m_fX, tImagePos.m_fY,
		GetWidth(), GetHeight(),
		RGB(255, 255, 255));

	if (eState == PLAYER::ATTACK)
	{
		if (eDirection == PLAYER::LEFT)
			Rectangle(_hdc, GetX() - cfPlayerAttackRange, GetY() - 10.f, GetX(), GetY() + 10.f);
		if (eDirection == PLAYER::RIGHT)
			Rectangle(_hdc, GetX() + cfPlayerAttackRange, GetY() - 10.f, GetX(), GetY() + 10.f);

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
		eState = PLAYER::RUN;
		eDirection = PLAYER::LEFT;
		m_fX -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		eState = PLAYER::RUN;
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
		if (m_bIsCollideCelling == true)
			return;

		eState = PLAYER::JUMP;
		if (m_iJumpCount == 2)
			return;
		else if (m_iJumpCount == 1)
		{
			m_fGravity = 0.f;
		}
		else if (m_iJumpCount == 0)
		{
			m_fJumpPower = 40.f;
			m_fJumpAngle = 40.f;
			m_fGravity = 0.f;
		}

		m_iJumpCount++;
	}

	// 공격하기
	if (GetAsyncKeyState('A') & 0x0001)
	{
		eState = PLAYER::ATTACK;
		Attack();
	}
}

void CPlayer::ActiveGravity()
{
	m_fY += m_fGravity;
	m_fGravity += GRAVITY;

	m_fY -= sinf(TO_RADIAN(m_fJumpAngle)) * m_fJumpPower;
}

void CPlayer::ResetPlayerVariable(void)
{
	//eState = PLAYER::IDLE;
	m_fGravity = 0.f;
	m_fJumpPower = 0.f;
	m_iJumpCount = 0;
}

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


	


