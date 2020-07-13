#pragma once


class CLine final
{
public :
	explicit CLine();
	explicit CLine(const LINEINFO& rLineInfo);
	virtual  ~CLine();
public:
	LINEINFO* Get_LineInfo() { return &m_tInfo; }
	void Render_Line(const HDC& _hdc);

private :
	LINEINFO m_tInfo;

};

