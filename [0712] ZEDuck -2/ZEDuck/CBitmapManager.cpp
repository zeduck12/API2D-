#include "framework.h"
#include "CBitmapManager.h"
#include "CMyBitmap.h"

CBitmapManager* CBitmapManager::m_pInstance = nullptr;
CBitmapManager::CBitmapManager()
{
}


CBitmapManager::~CBitmapManager()
{
	Release_BmpMgr();
}

HDC CBitmapManager::Find_Image_BmpMgr(const TCHAR* pImageKey)
{
	auto iter_find = m_mapBmp.find(pImageKey);
	if (iter_find == m_mapBmp.end())
		return nullptr;

	return iter_find->second->Get_MemDC();
}

void CBitmapManager::Insert_Texture_BmpMgr(const TCHAR* pFilePath, const TCHAR* pImageKey)
{
	// 키값으로 검사. 
	auto iter_find = find_if(m_mapBmp.begin(), m_mapBmp.end(), [&](auto& rPair)
		{
			return !lstrcmp(pImageKey, rPair.first);
		});
	// 키값이 end가 아니라는건 이미 이미지가 들어가 있다. 
	if (iter_find != m_mapBmp.end())
		return;
	//근데 키값이 end랴. 그럼? 없다. 집어넣어야지. 
	CMyBitmap* pBitmap = new CMyBitmap;
	pBitmap->LoadBmp(pFilePath);
	m_mapBmp.emplace(pImageKey, pBitmap);
}

void CBitmapManager::Release_BmpMgr()
{
	for (auto& rPair : m_mapBmp)
	{
		DeleteSafe(rPair.second);
	}
	m_mapBmp.clear();
}