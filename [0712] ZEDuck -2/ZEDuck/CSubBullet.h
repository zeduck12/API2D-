#pragma once
#include "CObj.h"

class CBullet;
class CSubBullet
	: public CObj
{
public:
    CSubBullet(CGameScene& _rGameScene, size_t _iWidth = ciBulletSize, size_t _iHeight = ciBulletSize, float _fSpeed = cfBulletSpeed, float _fDamage = cfBulletDamage, float _fDegree = cfBulletDegree);
    ~CSubBullet();

public:
    void SetBullet(CBullet* pBullet) { m_pBullet = pBullet; }
public:
    // CObj을(를) 통해 상속됨
    virtual void Ready(void) override;
    virtual int Update(float _fDeltaTime = 0.f) override;
    virtual void LateUpdate(void) override;
    virtual void Render(const HDC& _hdc) override;
    virtual void Release(void) override;

private:
    float m_fToX;
    float m_fToY;
    float m_fDamage;
    CBullet* m_pBullet = nullptr;
};

