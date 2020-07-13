#include "framework.h"
#include "CGroundManager.h"
#include "CGround.h"

// 스태틱변수 초기화
CGroundManager* CGroundManager::m_pInstance = nullptr;
CGroundManager::CGroundManager()
	:
	m_pGameScene(nullptr)
{
}

CGroundManager::~CGroundManager()
{
	Release_GroundManager();
}

bool CGroundManager::Ready_GroundManager(CGameScene& _rGameScene)
{
	m_pGameScene = &_rGameScene;
	SpawnGround(); // 여기서 그라운 생성해주기.

	return true;
}

void CGroundManager::Update_GroundManager()
{
	// n초에 한번씩 미리 생성된 그라운드 움직여주기.
	for (auto& pGround : m_listGound)
	{		
		pGround->Update();
	}
}

void CGroundManager::LateUpdate_GroundManager()
{
	for (auto& pGround : m_listGound)
	{
		pGround->LateUpdate();
	}
}

void CGroundManager::Render_GroundManager(const HDC& _hdc)
{
	for (auto& pGround : m_listGound)
	{
		pGround->Render(_hdc);
	}
}

void CGroundManager::Release_GroundManager()
{
	m_pGameScene = nullptr;
	for_each(m_listGound.begin(), m_listGound.end(), DeleteSafe<CGround*>);
}

void CGroundManager::SpawnGround()
{
	// 여기서 생성될 그라운드들 목록 채워주기.
	// (x, y, width, height)
	CGround* pGround = nullptr;
	pGround = new CGround(*m_pGameScene, GROUND_INFO(-50.f, 750.f, 100, 1500));
	m_listGound.emplace_back(pGround);

	pGround = new CGround(*m_pGameScene, GROUND_INFO(855.f, 1600.f, 4000, 200));  //밑바닥
	m_listGound.emplace_back(pGround);

	pGround = new CGround(*m_pGameScene, GROUND_INFO(500.f, 500.f, 400, 1100));   // 처음 내올때 오른쪽 기둥
	m_listGound.emplace_back(pGround);

	pGround = new CGround(*m_pGameScene, GROUND_INFO(1000.f, 1400.f, 300, 200));
	m_listGound.emplace_back(pGround);

	pGround = new CGround(*m_pGameScene, GROUND_INFO(1750.f, 1400.f, 700, 200));
	m_listGound.emplace_back(pGround);

	pGround = new CGround(*m_pGameScene, GROUND_INFO(2255.f, 1100.f, 300, 1200));
	m_listGound.emplace_back(pGround);

	pGround = new CGround(*m_pGameScene, GROUND_INFO(1750.f, 1150.f, 200, 50));
	m_listGound.emplace_back(pGround);

	pGround = new CGround(*m_pGameScene, GROUND_INFO(1450.f, 950.f, 200, 50));
	m_listGound.emplace_back(pGround);

	pGround = new CGround(*m_pGameScene, GROUND_INFO(1750.f, 750.f, 200, 50));
	m_listGound.emplace_back(pGround);

	pGround = new CGround(*m_pGameScene, GROUND_INFO(1950.f, 600.f, 200, 50));
	m_listGound.emplace_back(pGround);



}



