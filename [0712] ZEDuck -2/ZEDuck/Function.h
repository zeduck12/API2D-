#pragma once

class CObj;

template<typename T>
void DeleteSafe(T& rObj) {
	if (rObj) {
		delete rObj;
		rObj = nullptr;
	}
}

template<typename T>
void DeleteListSafe(list<T>& _list) {
	for (auto& pObj : _list) { DeleteSafe(pObj); }
	_list.clear();
}


// 라디안 계산기.
float GetRadian(float _iNum);

float GetRandomFloat(void);
// 최소 최대
int GetNumberMinBetweenMax(int _iMin, int _iMax);
float GetNumberMinBetweenMax(float _fMin, float _fMax);

void NormalizeVector(float& _fToX, float& _fToY);
void CollectGarbageObjects(list<CObj*>& _list);

bool IsCollided(const RECT& _rRect1, const RECT& _rRect2);
bool IsCollided(const CObj* _pObj1, const CObj* _pObj2);
bool IsCollided(const CObj* _pObj1, const CObj* _pObj2, RECT& _rCollidedPoint);


float GetDistance(const CObj* _CObj1, const CObj* _CObj2);

// IntersectRect -> 직접 구현하기.
bool MyIntersectRect(LPRECT lpRect, const RECT* _pRect1, const RECT* _pRect2);