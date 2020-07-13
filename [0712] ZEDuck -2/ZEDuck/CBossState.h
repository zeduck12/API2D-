#pragma once
#include "CBoss.h"

class CBossState
{
public:
	virtual void OnLoaded(CBoss* _pBoss) = 0;
	virtual void Update(CBoss* _pBoss, float _fDeltaTime = 0.f) = 0;

protected:
	void SetBossState(CBoss* _pBoss, CBossState* _pState)
	{
		_pBoss->SetState(_pState);
	}

protected:
	float fAccumulateTime = 0.f;
	float fStateDelay = 0.f;
};

class RunState : public CBossState
{
public:
	static RunState* Get_Instance()
	{
		if (instance == nullptr)
			instance = new RunState;

		return instance;
	}

	static void Destory_Instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	// CBossState을(를) 통해 상속됨
	virtual void OnLoaded(CBoss* _pBoss) override;
	virtual void Update(CBoss* _pBoss, float _fDeltaTime = 0.f) override;

private:
	static RunState* instance;

};

class IdleState : public CBossState
{
public:
	static IdleState* Get_Instance()
	{
		if (instance == nullptr)
			instance = new IdleState;

		return instance;
	}

	static void Destory_Instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	// CBossState을(를) 통해 상속됨
	virtual void OnLoaded(CBoss* _pBoss) override;
	virtual void Update(CBoss* _pBoss, float _fDeltaTime = 0.f) override;

private:
	static IdleState* instance;
};

class AttackState : public CBossState
{
public:
	static AttackState* Get_Instance()
	{
		if (instance == nullptr)
			instance = new AttackState;

		return instance;
	}

	static void Destory_Instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	// CBossState을(를) 통해 상속됨
	virtual void OnLoaded(CBoss* _pBoss) override;
	virtual void Update(CBoss* _pBoss, float _fDeltaTime = 0.f) override;

private:
	static AttackState* instance;
};

class AttackedState : public CBossState
{
public:
	static AttackedState* Get_Instance() 
	{
		if (instance == nullptr)
			instance = new AttackedState;

		return instance;
	}

	static void Destory_Instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	// CBossState을(를) 통해 상속됨
	virtual void OnLoaded(CBoss* _pBoss) override;
	virtual void Update(CBoss* _pBoss, float _fDeltaTime = 0.f) override;

private:
	static AttackedState* instance;
};

class TrackingState : public CBossState
{
public:
	static TrackingState* Get_Instance()
	{
		if (instance == nullptr)
			instance = new TrackingState;

		return instance;
	}

	static void Destory_Instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	// CBossState을(를) 통해 상속됨
	virtual void OnLoaded(CBoss* _pBoss) override;
	virtual void Update(CBoss* _pBoss, float _fDeltaTime = 0.f) override;

private:
	static TrackingState* instance;
};

class WaveAttackState : public CBossState
{
public:
	static WaveAttackState* Get_Instance()
	{
		if (instance == nullptr)
			instance = new WaveAttackState;

		return instance;
	}

	static void Destory_Instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	// CBossState을(를) 통해 상속됨
	virtual void OnLoaded(CBoss* _pBoss) override;
	virtual void Update(CBoss* _pBoss, float _fDeltaTime = 0.f) override;

private:
	static WaveAttackState* instance;
	float m_fWaveCoolTime = 1.f; // 쿨타임 시간.
	float m_fWaveAccumulateTime = 0.f; // 누적시간
};

class MeteorAttackState : public CBossState
{
public:
	static MeteorAttackState* Get_Instance()
	{
		if (instance == nullptr)
			instance = new MeteorAttackState;

		return instance;
	}

	static void Destory_Instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	// CBossState을(를) 통해 상속됨
	virtual void OnLoaded(CBoss* _pBoss) override;
	virtual void Update(CBoss* _pBoss, float _fDeltaTime = 0.f) override;

private:
	static MeteorAttackState* instance;
	float m_fMeteorCoolTime = 1.f; // 쿨타임 시간.
	float m_fMeteorAccumulateTime = 0.f; // 누적시간
};

class DoubleSideAttackState : public CBossState
{
public:
	static DoubleSideAttackState* Get_Instance()
	{
		if (instance == nullptr)
			instance = new DoubleSideAttackState;

		return instance;
	}

	static void Destory_Instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	// CBossState을(를) 통해 상속됨
	virtual void OnLoaded(CBoss* _pBoss) override;
	virtual void Update(CBoss* _pBoss, float _fDeltaTime = 0.f) override;

private:
	static DoubleSideAttackState* instance;
	float m_fAttackCoolTime = 1.f; // 쿨타임 시간.
	float m_fAttackAccumulateTime = 0.f; // 누적시간
	int m_iAttackCount = 0;
};

class FallState : public CBossState
{
public:
	static FallState* Get_Instance()
	{
		if (instance == nullptr)
			instance = new FallState;

		return instance;
	}

	static void Destory_Instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	// CBossState을(를) 통해 상속됨
	virtual void OnLoaded(CBoss* _pBoss) override;
	virtual void Update(CBoss* _pBoss, float _fDeltaTime = 0.f) override;

private:
	static FallState* instance;
	float m_fFallCoolTime = 5.f; // 쿨타임 시간.
	float m_fFallAccumulateTime = 0.f; // 누적시간
};

class JumpState : public CBossState
{
public:
	static JumpState* Get_Instance()
	{
		if (instance == nullptr)
			instance = new JumpState;

		return instance;
	}

	static void Destory_Instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	// CBossState을(를) 통해 상속됨
	virtual void OnLoaded(CBoss* _pBoss) override;
	virtual void Update(CBoss* _pBoss, float _fDeltaTime = 0.f) override;

private:
	static JumpState* instance;
	float m_fJumpCoolTime = 2.f; // 쿨타임 시간.
	float m_fJumpAccumulateTime = 0.f; // 누적시간
};






