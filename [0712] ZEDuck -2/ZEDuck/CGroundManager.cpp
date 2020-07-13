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

	CGround* pGround = nullptr;
	pGround = new CGround(*m_pGameScene, GROUND_INFO(1100.f, 500.f, 500, 100));
	m_listGound.emplace_back(pGround);
}



