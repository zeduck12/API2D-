#pragma once
class CMyBitmap
{
public:
	CMyBitmap();
	~CMyBitmap();
public:
	HDC Get_MemDC() { return m_hMemDC; }
	void LoadBmp(const TCHAR* pFilePath);
	void Release();
private:
	HDC m_hMemDC;
	HBITMAP m_OldBitmap;
	HBITMAP m_hBitmap;
};

