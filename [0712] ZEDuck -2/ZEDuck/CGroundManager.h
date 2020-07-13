#pragma once
#include "CGameScene.h"

class CGround;
class CGroundManager
{
public:
	static CGroundManager* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CGroundManager;

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	bool Ready_GroundManager(CGameScene& _rGameScene); // 그라운드 셋팅
	void Update_GroundManager(); // 그라운드 이동
	void LateUpdate_GroundManager(); // 그라운드 충돌
	void Render_GroundManager(const HDC& _hdc);
	void Release_GroundManager();

	// 그라운드 셋팅.
	void SpawnGround();

private:
	CGroundManager();
	~CGroundManager();

private:
	// 그라운드 매니저도 게임씬에 대한 정보를 들고 있어야함.
	CGameScene* m_pGameScene;

	list<CGround*> m_listGound; // 그라운드들을 담고 있을 리스트. 땅이 나중에 충돌되어 삭제가 될수 있으니 리스트로.
	static CGroundManager* m_pInstance;
};

