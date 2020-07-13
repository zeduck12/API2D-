#pragma once
#include "CObj.h"
class CAttackPattern :
    public CObj
{
public:
    CAttackPattern(CGameScene& _rGameWorld, CObj* _pOwner, MONSTER::E_PATTERN _ePattern);
    ~CAttackPattern();
public:
    // CObj을(를) 통해 상속됨
    virtual void Ready(void) {};
    virtual int Update(float _fDeltaTime = 0.f) override;
    virtual void LateUpdate(void) override;
    virtual void Release(void) override;

public:
    void WaveAttack(void);
    void Attack(void);
    bool CheckAttackRange(void);
    void Jump(); // 점프하는 함수.
    void MiniJump();
    void Tracking(void);
    bool DetectPlayer(void);
    void Patrol(void);
    bool IsOutOfRange(void);
public:
    void StartCrawlPattern(void);
    void StartRunPattern(void);
    void StartJumpPattern(void);
    void StartFlyPattern(void);
    void StartJuniorBossPattern(void);
    void StartLastBossPattern(void);

private:
    float m_fVec = 0.f; // 몬스터 직선움직방향에 쓰이는 방향벡터 변수
    float m_fSpeed = 0.f;
    CObj* m_pOwner = nullptr;
    MONSTER::E_PATTERN m_eMonsterPattern = MONSTER::PATTERN_END;

    // 딜레이 변수들
    int m_iAttackPatternDelay = 0;
    int m_iAttackTimeDelay = 0;
    float m_fAttackCoolTime = 0.f;

    // 점프패턴 관련 변수들
    float m_fJumpAngle = 40.f;
    float m_fJumpPower = 40.f;
    int m_iJumpCount = 0;
    bool m_bIsJump = false;

    // 플라이패턴 관련 변수들
    float m_fSpeedX = 0.f;
    float m_fSpeedY = 0.f;
    bool m_bIsReturnToHome = true;

    // 주니어보스패턴 관련 변수들
    bool m_bIsAttack = false;
};

