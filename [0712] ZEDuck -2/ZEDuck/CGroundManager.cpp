#include "framework.h"
#include "CGroundManager.h"
#include "CGround.h"

// ����ƽ���� �ʱ�ȭ
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
	SpawnGround(); // ���⼭ �׶�� �������ֱ�.

	return true;
}

void CGroundManager::Update_GroundManager()
{
	// n�ʿ� �ѹ��� �̸� ������ �׶��� �������ֱ�.
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
	// ���⼭ ������ �׶���� ��� ä���ֱ�.
	// (x, y, width, height)
	CGround* pGround = nullptr;
	pGround = new CGround(*m_pGameScene, GROUND_INFO(-50.f, 750.f, 100, 1500));
	m_listGound.emplace_back(pGround);

	pGround = new CGround(*m_pGameScene, GROUND_INFO(855.f, 1600.f, 4000, 200));  //�عٴ�
	m_listGound.emplace_back(pGround);

	pGround = new CGround(*m_pGameScene, GROUND_INFO(500.f, 500.f, 400, 1100));   // ó�� ���ö� ������ ���
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



