#pragma once
class CTexture;
class CResourcesManager
{
public:
	static CResourcesManager* Get_Instance()
	{
		if (instance == nullptr)
			instance = new CResourcesManager;
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

	bool Init(HINSTANCE _hInstance, const HDC& _hdc);
	class CTexture* LoadTexture(const string& _strKey,
		const wchar_t* _pFileName,
		const string& strPathKey = TEXTURE_PATH);
	class CTexture* FindTexture(const string& _strKey);
	class CTexture* GetBackBuffer() const { return m_pBackBuffer; }

private:
	CResourcesManager();
	~CResourcesManager();

	unordered_map<string, class CTexture*> m_mapTexture;
	HINSTANCE m_hInst;
	HDC m_hDC;
	CTexture* m_pBackBuffer;

	static CResourcesManager* instance;
};
