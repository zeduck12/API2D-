#include "framework.h"
#include "CTexture.h"
#include "CPathManager.h"

CTexture* CTexture::instance;
bool CTexture::LoadTexture(HINSTANCE _hInstance, const HDC& _hdc, const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	// �޸� DC�� ������ش�.
	m_hMemDC = CreateCompatibleDC(_hdc);
	const wchar_t* pPath = CPathManager::Get_Instance()->FindPath(strPathKey);
	wstring strPath;
	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	// ȭ�� �𾾿� �޸� ��
	m_hBitmap = (HBITMAP)LoadImage(_hInstance, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// ������ ������� ��Ʈ�� ������ DC�� �����Ѵ�.
	// �����Ҷ� ��ȯ�Ǵ� ���� DC�� �⺻���� ����Ǿ� �ִ�
	// ������ ��ȯ�ȴ�
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);
	// ���μ��� ũ��� ��� ������.

	return true;
}

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
	// ������ �����Ǿ� �ִ� ������ �ٽ� �������ش�.
	SelectObject(m_hMemDC, m_hOldBitmap);
	// ��Ʈ���� �����ش�
	DeleteObject(m_hBitmap);
	// DC�� �����ش�.
	DeleteDC(m_hMemDC);
}
