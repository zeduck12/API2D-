#pragma once
#include "CObj.h"
class CBossState;
class CBoss :
    public CObj
{
public:
    CBoss(CGameScene& _rGameScene, float _fX, float _fY, size_t _iWidth = ciMonsterSize, size_t _iHeight = ciMonsterSize, float _fHp = cfMonsterHp);
    CBoss(CGameScene& _rGameScene, size_t _iWidth = ciMonsterSize, size_t _iHeight = ciMonsterSize, float _fHp = cfMonsterHp);
    virtual ~CBoss();
public:
    // CObj을(를) 통해 상속됨
    virtual void Ready(void) {};
    virtual int Update(float _fDeltaTime = 0.f) override;
    virtual void LateUpdate(void) override;
    virtual void Render(const HDC& _hdc) override;
    virtual void Release(void) override;

public:
    bool DetectPlayer(void);
    void ActiveGravity(void);
    bool CheckAttackRange(void);
    void CheckDirection(void);
    void TakeDamage(float _fDamage) { m_fHp -= _fDamage; }
    void ReSetJumpCount(void) { m_iJumpCount = 0; }

public: // State
    void SetState(CBossState* _pState);

public: // Get & Set
    int  GetJumpCount(void) const { return m_iJumpCount; }
    void SetJumpCount(int _iJumpCount) { m_iJumpCount = _iJumpCount; }
    bool GetIsJump(void) const { return m_bIsJump; }
    void SetIsJump(bool _bIsJump) { m_bIsJump = _bIsJump; }
    float GetHp(void) const { return m_fHp; }
    float GetMaxHp(void) const { return m_fMaxHp; }
    size_t GetAttackedCount() const{ return m_iAttackedCount; }
    void SetAttackedCount(size_t _iCount) { m_iAttackedCount = _iCount; }
    bool GetIsFall() const { return m_bIsFall; }
    void SetIsFall(bool _bIsFall) { m_bIsFall = _bIsFall; }
    MONSTER::E_STATE GetBossState() const { return m_eState; }
    void SetBossState(MONSTER::E_STATE _eState) { m_eState = _eState; }
    void SetDirection(MONSTER::E_DIRECTION _eDir) { m_eDirection = _eDir; }
    void SetGravity(float _fGravity) { m_fGravity = _fGravity; }

private:
    // 점프관련 변수
    bool m_bIsJump = false;
    int m_iJumpCount = 0;
    float m_fGravity = 0.f;

    float m_fHp;
    float m_fMaxHp;
    float m_fDeltaTime = 0.f;
    size_t m_iAttackedCount = 0;
    bool m_bIsFall = false; // 나중에 5대 맞으면 넘어질때 상태체크용.
    MONSTER::E_DIRECTION m_eDirection = MONSTER::LEFT;
    MONSTER::E_STATE m_eState = MONSTER::IDLE;

    // 현재 보스 상태
    CBossState* m_eCurState = nullptr;
};

