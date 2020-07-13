#pragma once
#include "CObj.h"
class CGameScene;
class CBullet :
    public CObj
{
public:
    CBullet(CGameScene& _rGameScene, CObj* _pOwner,float _fX, float _fY, float _fToX, float _fToY, size_t _iWidth = ciBulletSize, size_t _iHeight = ciBulletSize, float _fSpeed = cfBulletSpeed, float _fDamage = cfBulletDamage, float _fDegree = cfBulletDegree);
    virtual ~CBullet();

public:
    // CObj을(를) 통해 상속됨
    virtual void Ready(void) override;
    virtual int Update(float _fDeltaTime = 0.f) override;
    virtual void LateUpdate(void) override;
    virtual void Render(const HDC& _hdc)	override;
    virtual void Release(void) override;

public:
    float GetDamage(void) const { return m_fDamage; }
private:
    
    float m_fToX;
    float m_fToY;
    float m_fDamage;
    float m_fTemp = 0.f; // 임시 각도 저장용.

    CObj* m_pOwner = nullptr;

};

