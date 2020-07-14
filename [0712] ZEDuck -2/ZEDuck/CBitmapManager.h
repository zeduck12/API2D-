#pragma once

class CMyBitmap;
class CBitmapManager
{
public:
	static CBitmapManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBitmapManager;
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
private:
	CBitmapManager();
	~CBitmapManager();
public:
	HDC Find_Image_BmpMgr(const TCHAR* pImageKey);
	void Insert_Texture_BmpMgr(const TCHAR* pFilePath, const TCHAR* pImageKey);
	void Release_BmpMgr();
private:
	static CBitmapManager* m_pInstance;
	map<const TCHAR*, CMyBitmap*> m_mapBmp;
};

