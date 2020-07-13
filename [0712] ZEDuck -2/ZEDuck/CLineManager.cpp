#include "framework.h"
#include "CLineManager.h"
#include "CLine.h"

CLineManager* CLineManager::m_pInstance = nullptr;
CLineManager::CLineManager()
{
}

CLineManager::~CLineManager()
{
	Release_LineManager();
}


void CLineManager::Ready_LineManager()
{
	//선들 좌표정해서 리스트에 넣어주기.
	/*
	(100, 900)
	(500, 900)
	(700, 900)
	(900, 700)
	*/

	// 직선 세개
	CLine* pLine = new CLine(LINEINFO(LINEPOS(100.f,900.f), LINEPOS(500.f, 900.f)));
	m_listLine.emplace_back(pLine);
	pLine = new CLine(LINEINFO(LINEPOS(500.f, 900.f), LINEPOS(700.f, 700.f)));
	m_listLine.emplace_back(pLine);
	pLine = new CLine(LINEINFO(LINEPOS(700.f, 700.f), LINEPOS(900.f, 700.f)));
	m_listLine.emplace_back(pLine);
}

void CLineManager::Render_LineManager(const HDC& _hdc)
{
	for (auto& pLine : m_listLine)
	{
		pLine->Render_Line(_hdc);
	}
}

void CLineManager::Release_LineManager()
{
	for_each(m_listLine.begin(), m_listLine.end(), DeleteSafe<CLine*>);
}

