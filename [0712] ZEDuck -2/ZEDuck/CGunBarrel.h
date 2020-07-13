#pragma once
#include "CObj.h"

class CGameScene;
class CGunBarrel :
    public CObj
{
public:
    CGunBarrel(CGameScene& _rGameScene, CObj* _pOwner, float _fDegree = 0.f, float _fLength = 20.f, float _fSpeed = 20.f);
    ~CGunBarrel();
public:
    // CObj을(를) 통해 상속됨
    virtual void Ready(void) override;
    virtual int Update(float _fDeltaTime = 0.f) override;
    virtual void LateUpdate(void) override;
    virtual void Render(const HDC& _hdc) override;
    virtual void Release(void) override;
public:
    float GetStartX(void) const { return CObj::GetX(); }
    float GetStartY(void) const { return CObj::GetY(); }
    float GetEndX(void) const { return GetStartX() + m_fLength * DIR_X_DEGREE(m_fDegree); }
    float GetEndY(void) const { return GetStartY() + m_fLength * DIR_Y_DEGREE(m_fDegree); }
    float GetDirX(void) const { return DIR_X_DEGREE(m_fDegree); }
    float GetDirY(void) const { return DIR_Y_DEGREE(m_fDegree); }
    float GetLength(void) const { return m_fLength; }

    void RotateCW(void) { m_fDegree += GetSpeed(); m_fDegree = CLAMP_DEGREE(m_fDegree); }
    void RotateCCW(void) { m_fDegree -= GetSpeed(); m_fDegree = CLAMP_DEGREE(m_fDegree); }

private:
    CObj* m_pOwner;
    float m_fDegree;
    float m_fLength;
};

