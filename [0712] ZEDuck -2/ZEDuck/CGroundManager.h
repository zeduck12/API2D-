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
	bool Ready_GroundManager(CGameScene& _rGameScene); // �׶��� ����
	void Update_GroundManager(); // �׶��� �̵�
	void LateUpdate_GroundManager(); // �׶��� �浹
	void Render_GroundManager(const HDC& _hdc);
	void Release_GroundManager();

	// �׶��� ����.
	void SpawnGround();

private:
	CGroundManager();
	~CGroundManager();

private:
	// �׶��� �Ŵ����� ���Ӿ��� ���� ������ ��� �־����.
	CGameScene* m_pGameScene;

	list<CGround*> m_listGound; // �׶������ ��� ���� ����Ʈ. ���� ���߿� �浹�Ǿ� ������ �ɼ� ������ ����Ʈ��.
	static CGroundManager* m_pInstance;
};

