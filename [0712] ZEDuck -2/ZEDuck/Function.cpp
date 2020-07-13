#include "framework.h"
#include "Function.h"
#include "CObj.h"

float GetRadian(float _iNum)
{
	return _iNum * (PI / 180);
}

void NormalizeVector(float& _fToX, float& _fToY)
{
	float fVectorLength = sqrtf(_fToX * _fToX + _fToY * _fToY);
	_fToX /= fVectorLength;
	_fToY /= fVectorLength;
}

bool IsCollided(const RECT& _rRect1, const RECT& _rRect2)
{
	return false;
}

bool IsCollided(const CObj* _pObj1, const CObj* _pObj2)
{
	return false;
}

bool IsCollided(const CObj* _pObj1, const CObj* _pObj2, RECT& _rCollidedPoint)
{
	if (!IS_VALID_OBJ(_pObj1) || !IS_VALID_OBJ(_pObj2)) return false;
	return /*IntersectRect*/MyIntersectRect(&_rCollidedPoint, &(_pObj1->GetRect()), &(_pObj2->GetRect()));
}

float GetDistance(const CObj* _CObj1, const CObj* _CObj2)
{
	// x 변화량
	float fX = _CObj1->GetX() - _CObj2->GetX();
	// y 변화량
	float fY = _CObj1->GetY() - _CObj2->GetY();

	// 거리
	float fDistance = sqrtf(fX*fX + fY*fY);

	return fDistance;
}

bool IntersectRect(RECT& rc1, RECT& rc2)
{
	if (rc1.left < rc2.right &&
		rc1.top < rc2.bottom &&
		rc1.right > rc2.left &&
		rc1.bottom > rc2.top) {
		return true;
	}
	else return false;
}

bool MyIntersectRect(LPRECT lpRect, const RECT* _pRect1, const RECT* _pRect2)
{
	if (_pRect1->left > _pRect2->right) return false;
	if (_pRect1->right < _pRect2->left) return false;
	if (_pRect1->top > _pRect2->bottom) return false;
	if (_pRect1->bottom < _pRect2->top) return false;

	// 플레이어, 몬스터 중심 구하기
	POINT playerPt = {};
	POINT monsterPt = {};

	playerPt.x = _pRect1->left + (_pRect1->right - _pRect1->left) >> 1;
	playerPt.y = _pRect1->top + (_pRect1->bottom - _pRect1->top) >> 1;

	monsterPt.x = _pRect2->left + (_pRect2->right - _pRect2->left) >> 1;
	monsterPt.y = _pRect2->top + (_pRect2->bottom - _pRect2->top) >> 1;

	// 플레이어 기준으로 몬스터가 좌상단
	if (playerPt.x > monsterPt.x && playerPt.y > monsterPt.y)
	{
		lpRect->left = _pRect1->left;
		lpRect->top = _pRect1->top;
		lpRect->right = _pRect2->right;
		lpRect->bottom = _pRect2->bottom;
	}
	// 플레이어 기준으로 몬스터가 좌하단
	else if (playerPt.x > monsterPt.x && playerPt.y < monsterPt.y)
	{
		lpRect->left = _pRect1->left;
		lpRect->top = _pRect2->top;
		lpRect->right = _pRect2->right;
		lpRect->bottom = _pRect1->bottom;
	}
	// 플레이어 기준으로 몬스터가 우상단
	else if (playerPt.x < monsterPt.x && playerPt.y > monsterPt.y)
	{
		lpRect->left = _pRect2->left;
		lpRect->top = _pRect1->top;
		lpRect->right = _pRect1->right;
		lpRect->bottom = _pRect2->bottom;
	}
	// 플레이어 기준으로 몬스터가 우하단
	else if (playerPt.x < monsterPt.x && playerPt.y < monsterPt.y)
	{
		lpRect->left = _pRect2->left;
		lpRect->top = _pRect2->top;
		lpRect->right = _pRect1->right;
		lpRect->bottom = _pRect1->bottom;
	}
	// 플레이어 기준으로 몬스터가 바로 위
	else if (playerPt.x == monsterPt.x && playerPt.y > monsterPt.y)
	{
		lpRect->left = _pRect1->left;
		lpRect->top = _pRect1->top;
		lpRect->right = _pRect2->right;
		lpRect->bottom = _pRect2->bottom;
	}
	// 플레이어 기준으로 몬스터가 바로 아래
	else if (playerPt.x == monsterPt.x && playerPt.y < monsterPt.y)
	{
		lpRect->left = _pRect2->left;
		lpRect->top = _pRect2->top;
		lpRect->right = _pRect1->right;
		lpRect->bottom = _pRect1->bottom;
	}
	// 플레이어 기준으로 몬스터가 바로 오른쪽
	else if (playerPt.x < monsterPt.x && playerPt.y == monsterPt.y)
	{
		lpRect->left = _pRect2->left;
		lpRect->top = _pRect2->top;
		lpRect->right = _pRect1->right;
		lpRect->bottom = _pRect1->bottom;
	}
	// 플레이어 기준으로 몬스터가 바로 왼쪽
	else if (playerPt.x > monsterPt.x && playerPt.y == monsterPt.y)
	{
		lpRect->left = _pRect1->left;
		lpRect->top = _pRect1->top;
		lpRect->right = _pRect2->right;
		lpRect->bottom = _pRect2->bottom;
	}

	return true;
}

void CollectGarbageObjects(list<CObj*>& _list)
{
	for (auto& pObj : _list) { DO_IF_IS_NOT_VALID_OBJ(pObj) { DeleteSafe(pObj); } }
	_list.remove_if([](auto& pObj) { return pObj == nullptr; });
}

float GetRandomFloat(void)
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

int GetNumberMinBetweenMax(int _iMin, int _iMax)
{
	if (_iMin > _iMax) abort();
	return rand() % (_iMax - _iMin + 1) + _iMin;
}

float GetNumberMinBetweenMax(float _fMin, float _fMax)
{
	if (_fMin > _fMax) abort();
	float fT = GetRandomFloat();
	return _fMin * (1.f - fT) + _fMax * fT;
}


