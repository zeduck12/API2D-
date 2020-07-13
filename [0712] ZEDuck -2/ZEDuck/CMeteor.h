#pragma once
#include "CObj.h"
class CMeteor :
    public CObj
{
public:
    CMeteor(CGameScene& _rGameScene, CObj* _pOwner, float _fX, float _fY, float _fToX, float _fToY, size_t _iWidth = ciMeteorSize, size_t _iHeight = ciMeteorSize, float _fSpeed = cfMeteorSpeed, float _fDamage = cfMeteorDamage, float _fDegree = cfMeteorDegree);
    virtual ~CMeteor();
public:
    virtual void Ready(void) override;
    virtual int Update(float _fDeltaTime = 0.f) override;
    virtual void LateUpdate(void) override;
    virtual void Render(const HDC& _hdc) override;
    virtual void Release(void) override;
public:
    float GetDamage(void) const { return m_fDamage; }
private:
    float m_fToX;
    float m_fToY;
    float m_fDamage;

    CObj* m_pOwner = nullptr;
};

