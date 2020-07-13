#pragma once
#include "CObj.h"
class CAttackPattern;
class CMonster :
    public CObj
{
public:
    CMonster(CGameScene& _rGameScene, float _fX, float _fY, size_t _iWidth = ciMonsterSize, size_t _iHeight = ciMonsterSize, float _fHp = cfMonsterHp, MONSTER::E_PATTERN _ePattern = MONSTER::CRAWL);
    CMonster(CGameScene& _rGameScene, size_t _iWidth = ciMonsterSize, size_t _iHeight = ciMonsterSize, float _fHp = cfMonsterHp, MONSTER::E_PATTERN _ePattern = MONSTER::CRAWL);
    virtual ~CMonster();
public:
    // CObj을(를) 통해 상속됨
    virtual void Ready(void) override;
    virtual int Update(float _fDeltaTime = 0.f) override;
    virtual void LateUpdate(void) override;
    virtual void Render(const HDC& _hdc) override;
    virtual void Release(void) override;
public:
    bool IsDied(void) { return m_fHp <= 0.f; }
    void TakeDamage(float _fDamage) { m_fHp -= _fDamage; }
    void Knockback(PLAYER::E_DIRECTION _eDir);
    void ActiveGravity(void);

public:

    void SetGravity(float _fGravity) { m_fGravity = _fGravity; }
    float GetHp(void) const { return m_fHp; }
    float GetMaxHp(void) const { return m_fMaxHp; }
    void SetDirection(void);
    MONSTER::E_STATE GetMonsterState() const { return m_eState; }
    void SetMonsterState(MONSTER::E_STATE _eState) { m_eState = _eState; }
    bool GetIsKnockBack(void) const { return m_bIsKnockBack; }
    void SetIsKnockBack(bool _bIsKnockBack) { m_bIsKnockBack = _bIsKnockBack; }
    float GetToX(void) const { return m_fToX; }
    float GetToY(void) const { return m_fToY; }
    void SetToX(float _fToX) { m_fToX = _fToX; NormalizeVector(m_fToX, m_fToY); }
    void SetToY(float _fToY) { m_fToY = _fToY; NormalizeVector(m_fToX, m_fToY); }
    void SetToXnY(float _fToX, float _fToY) { m_fToX = _fToX; m_fToY = _fToY; NormalizeVector(m_fToX, m_fToY); }

private:
    float m_fToX;
    float m_fToY;
    float m_fHp;
    float m_fMaxHp;

    // 몬스터도 중력받게
    float m_fGravity = 0.f;
  
    bool m_bIsKnockBack = false;
    CAttackPattern* m_pAttackPattern; // 장착 공격패턴
    MONSTER::E_PATTERN m_eMonsterPattern;
    MONSTER::E_STATE m_eState = MONSTER::IDLE;
    MONSTER::E_DIRECTION m_eDirection = MONSTER::LEFT;
};

