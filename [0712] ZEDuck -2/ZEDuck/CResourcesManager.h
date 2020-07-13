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

	bool Init(HINSTANCE _hInstance, HDC _hdc);
	class CTexture* LoadTexture(const string& _strKey,
		const wchar_t* _pFileName,
		const string& strPathKey = TEXTURE_PATH);
	class CTexture* FindTexture(const string& _strKey);


	CResourcesManager();
	~CResourcesManager();

	unordered_map<string, class CTexture*> m_mapTexture;
	HINSTANCE m_hInst;
	HDC m_hDC;

	static CResourcesManager* instance;
};
