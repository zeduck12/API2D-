#pragma once
class CPathManager
{
public:
	static CPathManager* Get_Instance()
	{
		if (instance == nullptr)
			instance = new CPathManager;
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

	bool Init();
	bool CreatePath(const string& strKey, const wchar_t* pPath,
		const string& strBasekey = ROOT_PATH);
	const wchar_t* FindPath(const string& strKey);

private:
	CPathManager();
	~CPathManager();

	unordered_map<string, wstring> m_mapPath;

	static CPathManager* instance;
};

