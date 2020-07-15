#include "framework.h"
#include "CAnimation.h"
#include "CBitmapManager.h"
#include "CMyBitmap.h"
#include "CObj.h"

CAnimation::CAnimation()
{
}

CAnimation::CAnimation(const CAnimation& _rOther)
{
	*this = _rOther;

	// 기존 클립정보 날려줌.
	m_mapClip.clear();
	map<string, ANIMATION_CLIP*>::const_iterator iter;
	map<string, ANIMATION_CLIP*>::const_iterator iterEnd = _rOther.m_mapClip.end();

	for (iter = _rOther.m_mapClip.begin() ; iter != iterEnd; ++iter)
	{
		ANIMATION_CLIP* pClip = new ANIMATION_CLIP;

		*pClip = *iter->second;
	}

	m_pCurClip = nullptr;
	m_strCurClip = "";
	SetCurrentClip(_rOther.m_strCurClip);
}

CAnimation::~CAnimation()
{
	for (auto& rPair : m_mapClip)
	{
		DeleteSafe(rPair.second);
	}
	m_mapClip.clear();
}

void CAnimation::SetCurrentClip(const string& _strCurClip)
{
	ChangeClip(_strCurClip);
}

void CAnimation::SetDefaultClip(const string& _strDefaultClip)
{
	m_strDefaultClip = _strDefaultClip;
}

void CAnimation::ChangeClip(const string& _strClip)
{
	if (m_strCurClip == _strClip)
		return;

	m_strCurClip = _strClip;

	if (m_pCurClip)
	{
		m_pCurClip->iFrameX = m_pCurClip->iStartX;
		m_pCurClip->iFrameY = m_pCurClip->iStartY;
		m_pCurClip->fAnimationTime = 0.f;
		m_pCurClip->fOptionTime = 0.f;
	}

	m_pCurClip = FindClip(_strClip);

	if (m_pCurClip->eType == ANIMATION::ATLAS)
		m_pOwner->SetMyBitmap(m_pCurClip->vecTexture[0]);
	else if (m_pCurClip->eType == ANIMATION::FRAME)
		m_pOwner->SetMyBitmap(m_pCurClip->vecTexture[m_pCurClip->iFrameX]);

}

ANIMATION_CLIP* CAnimation::FindClip(const string& _strName)
{
	map<string, ANIMATION_CLIP*>::iterator iter = m_mapClip.find(_strName);

	if (iter == m_mapClip.end())
		return nullptr;

	return iter->second;
}

bool CAnimation::Init()
{
	return false;
}

void CAnimation::Update(float _fTime)
{
	m_pCurClip->fAnimationTime += _fTime;

	while (m_pCurClip->fAnimationTime >= m_pCurClip->fAnimationFrameTime)
	{
		m_pCurClip->fAnimationTime -= m_pCurClip->fAnimationFrameTime;

		++m_pCurClip->iFrameX;
		if (m_pCurClip->iFrameX - m_pCurClip->iStartX == m_pCurClip->iLengthX)
		{
			m_pCurClip->iFrameX = m_pCurClip->iStartX;
			++m_pCurClip->iFrameY;

			if (m_pCurClip->iFrameY - m_pCurClip->iStartY == m_pCurClip->iLengthY)
			{
				m_pCurClip->iFrameY = m_pCurClip->iStartY;

				// 전부다 돌았다면 애니매이션을
				switch (m_pCurClip->eOption)
				{
				case ANIMATION::ONCE_RETURN:
					ChangeClip(m_strDefaultClip);
					break;
				case ANIMATION::ONCE_DESTROY:
					m_pOwner->SetValid(false);
					break;
				case ANIMATION::TIME_RETURN:
					break;
				case ANIMATION::TIME_DESTROY:
					break;
				}
			}
		}
	}
}

CAnimation* CAnimation::Clone()
{
	return new CAnimation(*this);
}

bool CAnimation::AddClip(const string& strName, ANIMATION::TYPE eType, ANIMATION::OPTION eOption, 
	float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
	int iLengthX, int iLengthY, float fOptionLimitTime, const string& strTextKey, const TCHAR* pFilePath)
{
	ANIMATION_CLIP* pClip = new ANIMATION_CLIP;
	pClip->eType = eType;
	pClip->eOption = eOption;
	pClip->fAnimationLimitTime = fAnimationLimitTime;
	pClip->iFrameMaxX = iFrameMaxX;
	pClip->iFrameMaxY = iFrameMaxY;
	pClip->iStartX = iStartX;
	pClip->iStartY = iStartY;
	pClip->iLengthX = iLengthX;
	pClip->iLengthY = iLengthY;
	pClip->fOptionLimitTime = fOptionLimitTime;
	pClip->fAnimationFrameTime = fAnimationLimitTime / (iLengthX * iLengthY); // 한사진당 머무르는 시간.
	
	CMyBitmap* pBitmap = new CMyBitmap;
	pBitmap->LoadBmp(pFilePath);
	// 로드한 텍스쳐 넣어주기.
	pClip->vecTexture.push_back(pBitmap);

	pClip->fAnimationTime= 0.f;
	pClip->iFrameX = iStartX;
	pClip->iFrameY = iStartY;
	pClip->fOptionTime = 0.f;

	m_mapClip.insert(make_pair(strName, pClip));

	if (m_strDefaultClip.empty())
		SetDefaultClip(strName);

	if (m_strCurClip.empty())
		SetCurrentClip(strName);

	return true;
}
