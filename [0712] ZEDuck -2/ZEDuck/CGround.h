#pragma once
#include "CObj.h"

typedef struct tagGroundInfo
{
    // 그라운드의 중심 좌표와 크기.
    tagGroundInfo()
    {
        ZeroMemory(this, sizeof(tagGroundInfo));
    }

    tagGroundInfo(float _fX , float _fY, size_t _iWidth, size_t _iHeight)
        :
        fX(_fX), fY(_fY),
        iWidth(_iWidth), iHeight(_iHeight)
    { }

    tagGroundInfo(const tagGroundInfo& _other)
        :
        fX(_other.fX), fY(_other.fY),
        iWidth(_other.iWidth), iHeight(_other.iHeight)
    { }

    // 위치
    float fX;
    float fY;
    // 크기
    size_t iWidth;
    size_t iHeight;

}GROUND_INFO;

class CGround 
{
public:
    CGround(const GROUND_INFO& _rInfo);
    ~CGround();

public:
    void Ready(void) ;
    int Update(float _fDeltaTime = 0.f) ;
    void LateUpdate(void) ;
    void Render(const HDC& _hdc) ;
    void Release(void) ;

private:
    GROUND_INFO m_tInfo;

    // 땅은 일정한 시간에 맞게 등장하고 움직임.
    float m_fSpeed;

};

