#pragma once
class CTexture
{
public:
	static CTexture* Get_Instance()
	{
		if (instance == nullptr)
			instance = new CTexture;
		return instance;
	}

	static void Destroy_Instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

public:
	HDC GetDC() const { return m_hMemDC; }
	bool LoadTexture(HINSTANCE _hInstance, HDC _hdc, const string& strKey,
		const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);

private:
	friend class CResourcesManager;
private:
	CTexture();
	~CTexture();

	HDC m_hMemDC;
	HBITMAP m_hBitmap; // h������ �ڵ�. ��Ʈ���� ��Ʈ�� �ϱ� ���� �ڵ� // ��, �׸��� ����
	HBITMAP m_hOldBitmap; // 
	BITMAP m_tInfo;

	static CTexture* instance;
};

