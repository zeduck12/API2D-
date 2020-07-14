#include "framework.h"
#include "CObj.h"
#include "CTexture.h"
#include "CResourcesManager.h"
#include "CAnimation.h"

CObj::CObj(CGameScene& _rGameScene)
	:
	m_rGameScene(_rGameScene),
	m_bIsValid(true),
	m_fX(0.f),
	m_fY(0.f),
	m_iWidth(10),
	m_iHeight(10),
	m_fSpeed(0.f),
	m_pDrawFunc(Rectangle)
{
}

CObj::CObj(CGameScene& _rGameScene, float _fX /*= 0*/, float _fY /*= 0*/,
	size_t _iWidth /*= 10*/, size_t _iHeight /*= 10*/, float _fSpeed /*= 0.f*/, float _fDegree /*=0.f*/,
	BOOL(__stdcall* _pDrawFunc) (HDC hdc, int _left, int _right, int _top, int _bottom) /*= Rectangle*/)
	:
	m_rGameScene(_rGameScene),
	m_bIsValid(true),
	m_fX(_fX),
	m_fY(_fY),
	m_iWidth(_iWidth),
	m_iHeight(_iHeight),
	m_fSpeed(_fSpeed),
	m_fDegree(_fDegree),
	m_pDrawFunc(_pDrawFunc)
{
}


CObj::~CObj()
{
}

void CObj::SaveInfo(FILE* _fpOut)
{
}

void CObj::LoadInfo(FILE* _fpIn)
{
}

void CObj::MoveTo(float _fDeltaX, float _fDeltaY)
{
	m_fX += _fDeltaX;
	m_fY += _fDeltaY;
}

void CObj::SetTexture(CTexture* pTexture)
{
	if (m_pTexture)
	{
		m_pTexture = nullptr;
		m_pTexture = pTexture;
	}
}

void CObj::SetTexture(const string& strkey, const wchar_t* pFileName, const string& strPathKey)
{
	if (pFileName)
	{
		if (m_pTexture)
			m_pTexture = nullptr;

		m_pTexture = CResourcesManager::Get_Instance()->LoadTexture(
			strkey, pFileName, strPathKey);
	}
}

CAnimation* CObj::CreateAnimation(const string& _strTag)
{
	if (m_pAnimation)
	{
		delete m_pAnimation;
		m_pAnimation = nullptr;
	}

	m_pAnimation = new CAnimation;

	m_pAnimation->SetTag(_strTag);
	m_pAnimation->SetOwner(this);
	if (!m_pAnimation->Init())
		return nullptr;

	return nullptr;
}

bool CObj::AddAnimationClip(const string& strName, ANIMATION::TYPE eType, ANIMATION::OPTION eOption,
	float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
	int iLengthX, int iLengthY, float fOptionLimitTime, const string& strTextKey, const TCHAR* pFilePath)
{
	if (!m_pAnimation)
		return false;

	m_pAnimation->AddClip(strName,eType, eOption, fAnimationLimitTime, iFrameMaxX, iFrameMaxY,
		iStartX, iStartY, iLengthX, iLengthY, fOptionLimitTime, strTextKey, pFilePath);

	return true;
}
