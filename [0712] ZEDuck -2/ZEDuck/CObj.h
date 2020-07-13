#pragma once
#include "CTexture.h"

class CGameScene;
class CObj abstract
{
public:
	CObj(CGameScene& _rGameScene);
	CObj(CGameScene& _rGameScene, float _fX = 0, float _fY = 0, size_t _iWidth = 10, size_t _iHeight = 10, float _fSpeed = 0.f, float _fDegree = 0.f, BOOL(__stdcall* _pDrawFunc) (HDC hdc, int _left, int _right, int _top, int _bottom) = Rectangle);
	virtual ~CObj();

public:
	virtual void Ready(void) = 0;
	virtual int  Update(float _fDeltaTime = 0.f) = 0;
	virtual void LateUpdate(void) = 0;
	virtual void Release(void) = 0;
	virtual void Render(const HDC& _hdc) { if (m_pDrawFunc) m_pDrawFunc(_hdc, GetLeft(), GetTop(), GetRight(), GetBottom()); };

	// 파일 입출력 관련
	virtual void SaveInfo(FILE* _fpOut);
	virtual void LoadInfo(FILE* _fpIn);

public:
	CGameScene& GetGameScene(void) const { return m_rGameScene; }

public:
	void MoveTo(float _fDeltaX, float _fDeltaY);
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	float GetSpeed() const { return m_fSpeed; }
	void SetX(float _fX) { m_fX = _fX; }
	void SetY(float _fY) { m_fY = _fY; }
	float GetX(void) const { return m_fX; }
	float GetY(void) const { return m_fY; }
	int GetLeft(void) const { return static_cast<int>(m_fX - (m_iWidth >> 1)); }
	int GetTop(void) const { return static_cast<int>(m_fY - (m_iHeight >> 1)); }
	int GetRight(void) const { return static_cast<int>(m_fX + (m_iWidth >> 1)); }
	int GetBottom(void) const { return static_cast<int>(m_fY + (m_iHeight >> 1)); }
	RECT GetRect(void) const {
		RECT rc = {
		static_cast<LONG>(m_fX - (m_iWidth >> 1)),
		static_cast<LONG>(m_fY - (m_iHeight >> 1)),
		static_cast<LONG>(m_fX + (m_iWidth >> 1)),
		static_cast<LONG>(m_fY + (m_iHeight >> 1))
		};
		return rc;
	}
	void SetWidth(size_t _iWidth) { m_iWidth = _iWidth; }
	void SetHeight(size_t _iHeight) { m_iHeight = _iHeight; }
	size_t GetWidth(void) const { return m_iWidth; }
	size_t GetHeight(void) const { return m_iHeight; }
	void SetValid(bool _bIsValid) { m_bIsValid = _bIsValid; }
	bool IsValid(void) const { return m_bIsValid; }

	// 텍스쳐 셋팅 함수.
public:
	void SetTexture(class CTexture* pTexture);
	void SetTexture(const string& strkey, const wchar_t* pFileName = NULL, const string& strPathKey = TEXTURE_PATH);

protected:
	bool m_bIsValid;
	float m_fX;
	float m_fY;
	float m_fSpeed;
	float m_fDegree;
	size_t m_iWidth;
	size_t m_iHeight;
	CTexture* m_pTexture;
	BOOL(__stdcall* m_pDrawFunc) (HDC hdc, int _left, int _right, int _top, int _bottom);

private:
	// CObj는 무조건 GameScene 객체를 지녀야만 한다.
	CGameScene& m_rGameScene;
};


