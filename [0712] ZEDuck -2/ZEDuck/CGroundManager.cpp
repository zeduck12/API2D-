#include "framework.h"
#include "CGroundManager.h"
#include "CGround.h"

// 스태틱변수 초기화
CGroundManager* CGroundManager::m_pInstance = nullptr;

CGroundManager::CGroundManager()
{
}

CGroundManager::~CGroundManager()
{
	Release_GroundManager();
}

void CGroundManager::Ready_GroundManager()
{
	//oldTime = GetTickCount();
	//CGround* pGround = nullptr;
	//for (size_t i = 0; i < 5; i++)
	//{
	//	// 그라운드를 생성하고 위치를 넣어준다,.
	//	// 중심과 크기
	//	pGround = new CGround(GROUND_INFO(1100.f + (i* 600), 500.f, 500, 100));
	//	m_listGound.emplace_back(pGround);
	//}

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
	for_each(m_listGound.begin(), m_listGound.end(), DeleteSafe<CGround*>);
}

void CGroundManager::SpawnGround()
{
	CGround* pGround = nullptr;
	pGround = new CGround(GROUND_INFO(1100.f, 500.f, 500, 100));
	m_listGound.emplace_back(pGround);
}



