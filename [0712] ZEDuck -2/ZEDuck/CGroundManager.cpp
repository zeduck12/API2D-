#include "framework.h"
#include "CGroundManager.h"
#include "CGround.h"

// ����ƽ���� �ʱ�ȭ
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
	//	// �׶��带 �����ϰ� ��ġ�� �־��ش�,.
	//	// �߽ɰ� ũ��
	//	pGround = new CGround(GROUND_INFO(1100.f + (i* 600), 500.f, 500, 100));
	//	m_listGound.emplace_back(pGround);
	//}

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
	for_each(m_listGound.begin(), m_listGound.end(), DeleteSafe<CGround*>);
}

void CGroundManager::SpawnGround()
{
	CGround* pGround = nullptr;
	pGround = new CGround(GROUND_INFO(1100.f, 500.f, 500, 100));
	m_listGound.emplace_back(pGround);
}



