#include "framework.h"
#include "CResourcesManager.h"
#include "CTexture.h"

CResourcesManager* CResourcesManager::instance;
bool CResourcesManager::Init(HINSTANCE _hInstance, const HDC& _hdc)
{
	m_hInst = _hInstance;
	m_hDC = _hdc;

	// 백버퍼를 불러온다.
	m_pBackBuffer = LoadTexture("BackBuffer", L"BackBuffer.bmp");
	return true;
}

CTexture* CResourcesManager::LoadTexture(const string& _strKey, const wchar_t* _pFileName, const string& strPathKey)
{
	CTexture* pTexture = FindTexture(_strKey);

	if (pTexture)
		return pTexture;


	pTexture = new CTexture;

	if (!pTexture->LoadTexture(m_hInst, m_hDC, _strKey, _pFileName, strPathKey))
	{
		delete pTexture;
		pTexture = nullptr;
		return NULL;
	}

	//pTexture->AddRef();
	m_mapTexture.insert(make_pair(_strKey, pTexture));

	return pTexture;
}

CTexture* CResourcesManager::FindTexture(const string& _strKey)
{
	unordered_map<string, class CTexture*>::iterator iter = m_mapTexture.find(_strKey);

	if (iter == m_mapTexture.end())
	{
		return NULL;
	}

	//iter->second->AddRef();

	return iter->second;
}

CResourcesManager::CResourcesManager()
{
}

CResourcesManager::~CResourcesManager()
{
	// SAFE_RELEASE(m_pBackBuffer);
	// Safe_Release_Map(m_mapTexture);
	if (m_pBackBuffer)
	{
		delete m_pBackBuffer;
		m_pBackBuffer = nullptr;
	}
}