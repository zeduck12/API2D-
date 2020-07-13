#include "framework.h"
#include "CGameScene.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CBullet.h"
#include "CSubBullet.h"
#include "CLineManager.h"
#include "CGroundManager.h"
#include "CBoss.h"
#include "CTimeManager.h"

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
	Release();
}

void CGameScene::Init(void)
{
	oldTime = GetTickCount();

	m_hDC = GetDC(g_hWND);
	// 랜덤값을 생성하기 위한 시드 전달.
	srand(static_cast<unsigned int>(time(nullptr)));

	// 플레이어 생성
	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer(*this, WINCX >> 1, WINCY - 100.f);
		m_pPlayer->Ready();
	}
	// 보스생성
	if (!m_pBoss)
	{
		m_pBoss = new CBoss(*this, (WINCX >> 1) + 400.f, WINCY - 100.f);
		m_pPlayer->Ready();
	}
	// 시작시간.
	m_iStartTime = int(CTimeManager::Get_Instance()->GetWorldTime() * 1000);

	// 몬스터 생성
	//CObj* pMonster = nullptr;
	//for (int i = 0; i < 5; i++) 
	//{
	//	pMonster = new CMonster( *this);
	//	pMonster->Ready();
	//	// 몬스터 리스트에 추가
	//	m_listMonsters.emplace_back(pMonster);
	//}

	//CObj* pMonster = new CMonster(*this, 600.f, WINCY - 500.f, ciMonsterSize, ciMonsterSize, cfMonsterHp, MONSTER::JUNIOR_BOSS);
	//pMonster->Ready();
	//m_listMonsters.emplace_back(pMonster);

}

void CGameScene::Update(void)
{
	float fDeltaTime = 0.f;
	fDeltaTime =  GetTickCount() - oldTime ;
	oldTime = GetTickCount();

	for (auto& pBullet : m_listBullets) { pBullet->Update(); }
	for (auto& pMeteor : m_listMeteors) { pMeteor->Update(); }
	for (auto& pMonster : m_listMonsters) { pMonster->Update(); }
	DO_IF_IS_VALID_OBJ(m_pPlayer) { m_pPlayer->Update(); }
	DO_IF_IS_VALID_OBJ(m_pBoss) { m_pBoss->Update(fDeltaTime); }
}

void CGameScene::LateUpdate(void)
{
	for (auto& pBullet : m_listBullets) { DO_IF_IS_VALID_OBJ(pBullet) { pBullet->LateUpdate(); } }
	for (auto& pMeteor : m_listMeteors) { DO_IF_IS_VALID_OBJ(pMeteor) { pMeteor->LateUpdate(); } }
	for (auto& pMonster : m_listMonsters) { DO_IF_IS_VALID_OBJ(pMonster) { pMonster->LateUpdate(); } }
	DO_IF_IS_VALID_OBJ(m_pPlayer) { m_pPlayer->LateUpdate(); }
	DO_IF_IS_VALID_OBJ(m_pBoss) { m_pBoss->LateUpdate(); }

	DO_IF_IS_NOT_VALID_OBJ(m_pPlayer) { DeleteSafe(m_pPlayer); }
	DO_IF_IS_NOT_VALID_OBJ(m_pBoss) { DeleteSafe(m_pBoss); }
	CollectGarbageObjects(m_listBullets);
	CollectGarbageObjects(m_listMeteors);
	CollectGarbageObjects(m_listMonsters);
}

void CGameScene::Render(void)
{
	// 플레이어가 중심에 있고 나머지들이 움직이도록

	DO_IF_IS_VALID_OBJ(m_pPlayer) 
	{
		XFORM xf = { 1,0,0,1,-m_pPlayer->GetX() + (WINCX>>1), -m_pPlayer->GetY() + (WINCY >> 1) };
		SetGraphicsMode(m_hDC, GM_ADVANCED);
		SetWorldTransform(m_hDC, &xf);
	}

	ClearWindowVer2();
	ShowStageWindow();
	
	for (auto& pMonster : m_listMonsters) { pMonster->Render(m_hDC); }
	for (auto& pBullet : m_listBullets) { pBullet->Render(m_hDC); }
	for (auto& pMeteor : m_listMeteors) { pMeteor->Render(m_hDC); }
	DO_IF_IS_VALID_OBJ(m_pPlayer) { m_pPlayer->Render(m_hDC); }
	DO_IF_IS_VALID_OBJ(m_pBoss) { m_pBoss->Render(m_hDC); }
}

void CGameScene::Release(void)
{
	DeleteSafe(m_pBoss);
	DeleteSafe(m_pPlayer);
	DeleteListSafe(m_listBullets);
	DeleteListSafe(m_listMeteors);
	DeleteListSafe(m_listMonsters);

	ReleaseDC(g_hWND, m_hDC);

}

inline void CGameScene::ShowStageGround(void)
{
	// 여기서 플레이어가 따라 움직일 그라운드 그려줌.
	POINT pt = {};
	MoveToEx(m_hDC, 500, 900, &pt);
	LineTo(m_hDC, 700, 700);
	LineTo(m_hDC, 900, 700);
}
