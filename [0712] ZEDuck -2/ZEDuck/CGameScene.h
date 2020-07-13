#pragma once

class CObj;

class CGameScene final
{
public:
	CGameScene();
	~CGameScene();
public:
	void Init(void);
	void Update(void);
	void LateUpdate(void);
	void Render(void);
	void Release(void);
public:
	CObj* GetPlayer(void) const { return m_pPlayer; }
	CObj* GetBoss(void) const { return m_pBoss; }
	list<CObj*>& GetMonsters(void) { return m_listMonsters; }
	list<CObj*>& GetBullets(void) { return m_listBullets; }

private:
	void Test(void) { return; }
	inline void ClearWindow(void) { Rectangle(m_hDC, 0, 0, WINCX, WINCY); }
	inline void ClearWindowVer2(void) { Rectangle(m_hDC, -10000, -10000, 10000, 10000); }
	inline void ShowStageWindow(void) { Rectangle(m_hDC, 100, 100, WINCX - 100, WINCY - 100); }
	inline void ShowStageGround(void);

private:
	DWORD oldTime;
	int m_iStartTime = 0;

	HDC m_hDC;
	CObj* m_pPlayer;
	CObj* m_pBoss;
	
	list<CObj*> m_listMonsters;
	list<CObj*> m_listBullets;
	list<CObj*> m_listMeteors;

	// 카메라처럼 이동할 수 있게 하는 변수들.
	// float m_fFlowX = 0.f;
	// 플레이어는 가만히 있고 맵들을 움직이게 하기.

	




};

