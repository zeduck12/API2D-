#pragma once
#pragma once

// â ������
#define WINCX 1000
#define WINCY 1000

// ���� ���
#define ROOT_PATH "RootPath"
#define TEXTURE_PATH "TexturePath"

// �߷� ���
#define GRAVITY 1.0f/*2.5f*/

// ������Ʈ ��ȿ�� üũ
#define IS_VALID_OBJ(_pObj)				((_pObj) && (_pObj->IsValid()))
#define DO_IF_IS_NOT_VALID_OBJ(_pObj)	if(!IS_VALID_OBJ(_pObj))
#define DO_IF_IS_VALID_OBJ(_pObj)		if(IS_VALID_OBJ(_pObj))

// �� ��ȯ ����
#define TO_BOSS(_pObj)			dynamic_cast<CBoss*>(_pObj)
#define TO_PLAYER(_pObj)		dynamic_cast<CPlayer*>(_pObj)
#define TO_BULLET(_pObj)		dynamic_cast<CBullet*>(_pObj)
#define TO_SUBBULLET(_pObj)		dynamic_cast<CSubBullet*>(_pObj)
#define TO_BOMB(_pObj)			dynamic_cast<CBomb*>(_pObj)
#define TO_SPACE(_pObj)			dynamic_cast<const CSpace*>(_pObj)
#define TO_MONSTER(_pObj)		dynamic_cast<CMonster*>(_pObj)
#define TO_ITEM_POWER(_pObj)	dynamic_cast<CItemPower*>(_pObj)
#define TO_ITEM_BUDDY(_pObj)	dynamic_cast<CItemBuddy*>(_pObj)

// ���� ����
#define PI acos(-1.f) //== acos(cos(pi)) == pi
#define TWO_PI (2.f * PI)

#define TO_RADIAN(_fDegree) ((_fDegree) * TWO_PI / 360.f)
#define TO_DEGREE(_fRadian) ((_fRadian) * 360.f / TWO_PI)

#define DIR_X_DEGREE(_fDegree) cosf(TO_RADIAN((_fDegree)))
#define DIR_Y_DEGREE(_fDegree) sinf(TO_RADIAN((_fDegree)))

#define DIR_X_RADIAN(_fRadian) cosf((_fRadian))
#define DIR_Y_RADIAN(_fRadian) sinf((_fRadian))

#define CLAMP_RADIAN(_fRadian) ((_fRadian) -static_cast<int>((_fRadian) / TWO_PI) * TWO_PI)
#define CLAMP_DEGREE(_fDegree) ((_fDegree) - static_cast<int>((_fDegree) / 360.f) * 360.f)

// ���� ����� ����
#define F_WRITE_DATA(_valueName, _fpOut)	fwrite(&(_valueName), sizeof(_valueName), 1, _fpOut)
#define F_READ_DATA(_valueName, _fpIn)		fread(&(_valueName), sizeof(_valueName), 1, _fpIn)
#define F_WRITE_HEAD(_valueName, _fpOut)	fwrite(&(_valueName), sizeof(_valueName), 1, _fpOut)
#define F_READ_HEAD(_valueName, _fpIn)		fread(&(_valueName), sizeof(_valueName), 1, _fpIn)
