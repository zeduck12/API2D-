#pragma once
#include "CObj.h"

class CGunBarrel;
class CShield;
class CPlayer :
    public CObj
{
public:
    CPlayer(CGameScene& _rGameScene);
    CPlayer(CGameScene& _rGameScene, float _fX, float _fY, size_t _iWidth = ciPlayerSize, size_t _iHeight = ciPlayerSize, float _fSpeed = cfPlayerSpeed, float _fDegree = cfPlayerDegree);
    virtual ~CPlayer();
public:
    virtual void Ready(void) override;
    virtual int Update(float _fDeltaTime = 0.f) override;
    virtual void LateUpdate(void) override;
    virtual void Render(const HDC& _hdc);
    virtual void Release(void) override;

public:
    void Attack();
    bool CheckAttackRange(CObj* pObj); // 공격범위안에 몬스터가 들어왔는지 true라면 어택함수에서 몬스터에게 데미지
    void InputKeyState();
    void ActiveGravity();

public:
    float GetDamage() const { return m_fDamage; }
    size_t GetLifeNum() const { return m_iLifeNum; }
    void   SetLifeNum(size_t _iLifeNum) { m_iLifeNum = _iLifeNum; }

private:
    size_t m_iLifeNum = 5;
    float m_fDamage = cfPlayerDamage;
    

    // 점프 관련 변수
    int m_iJumpCount = 0;
    float m_fJumpAngle = 40.f;
    float m_fJumpPower = 40.f;
    float m_fGravity = 0.f;

private:
    POINT oldPoint;
    bool m_bIsPressDown = false;
    PLAYER::E_STATE eState = PLAYER::IDLE; // 상태
    PLAYER::E_DIRECTION eDirection = PLAYER::DIRECTION_END; // 방향
};

