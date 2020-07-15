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
    void Attack(void);
    bool CheckAttackRange(CObj* pObj); // 공격범위안에 몬스터가 들어왔는지 true라면 어택함수에서 몬스터에게 데미지
    void InputKeyState(void);
    void ActiveGravity(void);
    void ResetPlayerVariable(void);

public:
    float  GetDamage(void) const { return m_fDamage; }
    size_t GetLifeNum(void) const { return m_iLifeNum; }
    void   SetLifeNum(size_t _iLifeNum) { m_iLifeNum = _iLifeNum; }
    void   SetGravity(float _fGravity) { m_fGravity = _fGravity; }
    bool   GetIsCollideCelling() const { return m_bIsCollideCelling; }
    void   SetIsCollideCelling(bool _bIsCollideCelling) { m_bIsCollideCelling = _bIsCollideCelling; }

private:
    size_t m_iLifeNum = 5;
    float m_fDamage = cfPlayerDamage;
    

    // 점프 관련 변수
    int m_iJumpCount = 0;
    float m_fJumpAngle = 40.f;
    float m_fJumpPower = 40.f;
    float m_fGravity = 0.f;
    bool m_bIsCollideCelling = false;

private:
    POINT oldPoint;
    bool m_bIsPressDown = false;
    bool m_bIsRunPress = false;
    PLAYER::E_STATE eState = PLAYER::IDLE; // 상태
    PLAYER::E_DIRECTION eDirection = PLAYER::DIRECTION_END; // 방향
};

