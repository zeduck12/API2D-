#include "framework.h"
#include "CMyBitmap.h"

CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
}

void CMyBitmap::LoadBmp(const TCHAR* pFilePath)
{
	HDC hDC = GetDC(g_hWND);
	// ��ȭ�� �غ�. 
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWND, hDC);
	// ����� ���� �غ�. 
	m_hBitmap = (HBITMAP)LoadImage(nullptr, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	// ���Ⱑ �׸��� �׸�. 
	m_OldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBitmap::Release()
{
	// ���õǾ� �ִ� GDI ������Ʈ�� ����� �ִ� ����� ����. 
	// �׷��� ���� �ִ������� ���� ���� �ְ� ���� ����� ���� �����. 
	// �׷��� OldBitmap�̶�³���� �����. 
	SelectObject(m_hMemDC, m_OldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
