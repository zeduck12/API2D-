#pragma once
// 구조체 하나, 하나가 모션 정보.
class CMyBitmap;
typedef struct tagAnimationClip
{
	ANIMATION::TYPE		eType;
	ANIMATION::OPTION	eOption;
	vector<CMyBitmap*>	vecTexture;

	float fAnimationTime;
	float fAnimationLimitTime;
	float fAnimationFrameTime;
	int iFrameX;
	int iFrameY;
	int iFrameMaxX;
	int iFrameMaxY;
	int iStartX;
	int iStartY;
	int iLengthX;
	int iLengthY;
	float fOptionTime;
	float fOptionLimitTime;

}ANIMATION_CLIP;


class CAnimation
{
private:
	friend class CObj;

private:
	CAnimation();
	CAnimation(const CAnimation& _rOther);
	~CAnimation();

private:
	map<string, ANIMATION_CLIP*> m_mapClip;
	string m_sTag;

	ANIMATION_CLIP* m_pCurClip = nullptr;
	string			m_strCurClip;
	string			m_strDefaultClip;
	CObj*			m_pOwner = nullptr;


public:
	ANIMATION_CLIP* GetCurrentClip() const { return m_pCurClip; }

	void SetOwner(CObj* _pObj) { m_pOwner = _pObj; }
	void SetCurrentClip(const string& _strCurClip);
	void SetDefaultClip(const string& _strDefaultClip);
	void ChangeClip(const string& _strClip);
	ANIMATION_CLIP* FindClip(const string& _strName);

	bool Init();
	void Update(float _fTime);
	CAnimation* Clone();
public:
	void SetTag(const string& _rStrTag) { m_sTag = _rStrTag; }
	bool AddClip(const string& strName, ANIMATION::TYPE eType,
		ANIMATION::OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
		int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTextKey, const TCHAR* pFilePath);
};

