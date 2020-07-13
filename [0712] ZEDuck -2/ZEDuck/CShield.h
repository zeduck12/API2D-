#pragma once
#include "CObj.h"
class CShield :
    public CObj
{
public:
    CShield(CGameScene& _rGameScene, size_t _iWidth = ciShieldSize, size_t _iHeight = ciShieldSize, float _fSpeed = cfShieldSpeed, float _fDegree = 0.f);
    ~CShield();
public:
    // CObj을(를) 통해 상속됨
    virtual void Ready(void) override;
    virtual int Update(float _fDeltaTime = 0.f) override;
    virtual void LateUpdate(void) override;
    virtual void Render(const HDC& _hdc) override;
    virtual void Release(void) override;
private:

};

