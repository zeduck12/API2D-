#include "framework.h"
#include "CTexture.h"
#include "CPathManager.h"

CTexture* CTexture::instance;
bool CTexture::LoadTexture(HINSTANCE _hInstance, const HDC& _hdc, const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	// 메모리 DC를 만들어준다.
	m_hMemDC = CreateCompatibleDC(_hdc);
	const wchar_t* pPath = CPathManager::Get_Instance()->FindPath(strPathKey);
	wstring strPath;
	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	// 화면 디씨용 메모리 디씨
	m_hBitmap = (HBITMAP)LoadImage(_hInstance, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 위에서 만들어준 비트맵 도구를 DC에 지정한다.
	// 지정할때 반환되는 값은 DC에 기본으로 지어되어 있단
	// 도구가 반환된다
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);
	// 가로세로 크기들 모두 가져옴.

	return true;
}

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
	// 기존에 지정되어 있던 도구를 다시 지정해준다.
	SelectObject(m_hMemDC, m_hOldBitmap);
	// 비트맵을 지워준다
	DeleteObject(m_hBitmap);
	// DC를 지워준다.
	DeleteDC(m_hMemDC);
}
