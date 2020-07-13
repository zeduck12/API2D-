#pragma once
class CLine;
class CLineManager
{
public:
	static CLineManager* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CLineManager;
			
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
	// ���� �غ��ϱ�.
	// ����ϱ�
	void Ready_LineManager();
	void Render_LineManager(const HDC& _hdc);
	void Release_LineManager();

private:
	CLineManager();
	~CLineManager();

private:
	list<CLine*> m_listLine;
	static CLineManager* m_pInstance;
};

