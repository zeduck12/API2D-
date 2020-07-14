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
#include "CPathManager.h"
#include "CResourcesManager.h"
#include "CTexture.h"
#include "CBitmapManager.h"
#include "CMyBitmap.h"


CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
	Release();
}

void CGameScene::Init(void)
{
	m_hDC = GetDC(g_hWND);
	CBitmapManager::Get_Instance()->Insert_Texture_BmpMgr(L"Texture\\Background.bmp", L"BackGround");
	CBitmapManager::Get_Instance()->Insert_Texture_BmpMgr(L"Texture\\BackBuffer.bmp", L"BackBuffer");
	HDC hBack = CBitmapManager::Get_Instance()->Find_Image_BmpMgr(L"BackBuffer");
	SetGraphicsMode(hBack, GM_ADVANCED);
	
	oldTime = GetTickCount();
	srand(static_cast<unsigned int>(time(nullptr)));	// 랜덤값을 생성하기 위한 시드 전달.


	if (!CGroundManager::Get_Instance()->Ready_GroundManager(*this))
		return;

	// 플레이어 생성
	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer(*this,/* WINCX >> 1*/100.f,/* WINCY - 100.f*/ 100.f);
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

	CObj* pMonster = new CMonster(*this, 500.f, 1400.f, ciMonsterSize, ciMonsterSize, cfMonsterHp, MONSTER::CRAWL);
	pMonster->Ready();
	m_listMonsters.emplace_back(pMonster);

	pMonster = new CMonster(*this, 1000.f, 1250.f, ciMonsterSize, ciMonsterSize, cfMonsterHp, MONSTER::CRUSH);
	pMonster->Ready();
	m_listMonsters.emplace_back(pMonster);

	pMonster = new CMonster(*this, 1750.f, 1250.f, ciMonsterSize, ciMonsterSize, cfMonsterHp, MONSTER::JUMP);
	pMonster->Ready();
	m_listMonsters.emplace_back(pMonster);

}

void CGameScene::Update(void)
{
	// 현재 델타타임 쓰지 않고 있는 중.
	float fDeltaTime = 0.f;
	fDeltaTime =  GetTickCount() - oldTime ;
	oldTime = GetTickCount();

	CGroundManager::Get_Instance()->Update_GroundManager();
	for (auto& pBullet : m_listBullets) { pBullet->Update(); }
	for (auto& pMeteor : m_listMeteors) { pMeteor->Update(); }
	for (auto& pMonster : m_listMonsters) { pMonster->Update(); }
	DO_IF_IS_VALID_OBJ(m_pPlayer) { m_pPlayer->Update(); }
	DO_IF_IS_VALID_OBJ(m_pBoss) { m_pBoss->Update(fDeltaTime); }
}

void CGameScene::LateUpdate(void)
{
	CGroundManager::Get_Instance()->LateUpdate_GroundManager();
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
	HDC hBack = CBitmapManager::Get_Instance()->Find_Image_BmpMgr(L"BackBuffer");
	if (nullptr == hBack)
		return;
	HDC hMemDC = CBitmapManager::Get_Instance()->Find_Image_BmpMgr(L"BackGround");
	if (nullptr == hMemDC)
		return;

	RECT rc{ 0,0, WINCX, WINCY };
	FillRect(hBack, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
	XFORM xf{ 1,0,0,1,0,0 };
	DO_IF_IS_VALID_OBJ(m_pPlayer) 
	{
		XFORM xf = { 1,0,0,1,-m_pPlayer->GetX() + (WINCX>>1), -m_pPlayer->GetY() + (WINCY >> 1) };
		SetWorldTransform(hBack, &xf);
	}
	//ClearWindowVer2();
	CGroundManager::Get_Instance()->Render_GroundManager(hBack);
	for (auto& pMonster : m_listMonsters) { pMonster->Render(hBack); }
	for (auto& pBullet : m_listBullets) { pBullet->Render(hBack); }
	for (auto& pMeteor : m_listMeteors) { pMeteor->Render(hBack); }
	DO_IF_IS_VALID_OBJ(m_pPlayer) { m_pPlayer->Render(hBack); }
	DO_IF_IS_VALID_OBJ(m_pBoss) { m_pBoss->Render(hBack); }
	XFORM xf2 = { 1,0,0,1,0, 0 };
	SetWorldTransform(hBack, &xf2);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
}

void CGameScene::Release(void)
{
	DeleteSafe(m_pBoss);
	DeleteSafe(m_pPlayer);
	DeleteListSafe(m_listBullets);
	DeleteListSafe(m_listMeteors);
	DeleteListSafe(m_listMonsters);

	CPathManager::Destroy_Instance();
	CResourcesManager::Destroy_Instance();
	CGroundManager::Destroy_Instance();
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
