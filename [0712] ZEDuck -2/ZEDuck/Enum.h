#pragma once

namespace OBJ 
{
	enum E_DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_END };
	enum E_COLLIDED { COL_LEFT, COL_RIGHT, COL_TOP, COL_BOTTOM, COL_END };
}

namespace MONSTER
{
	enum E_TYPE { TYPE_NORMAL, TYPE_BOSS, TYPE_END }; // ���� �Ⱦ�.
	enum E_STATE { IDLE, RUN, TRACKING, ATTACK, ATTACKED, STATE_END};
	enum E_PATTERN { CRAWL, CRUSH, JUMP, FLY, JUNIOR_BOSS, LAST_BOSS, PATTERN_END};
	enum E_DIRECTION { LEFT, RIGHT, UP, DOWN, DIRECTION_END };
}

namespace BULLET
{
	enum E_TYPE { TYPE_MONSTER, TYPE_PLAYER, TYPE_END };
}

namespace PLAYER
{
	enum E_STATE { IDLE, ATTACK, RUN, JUMP, STATE_END };
	enum E_DIRECTION { LEFT, RIGHT, UP, DOWN, DIRECTION_END};
}

namespace ANIMATION
{
	enum TYPE { ATLAS, FRAME, TYPE_END};
	enum OPTION 
	{
		LOOP,		  // �ַ� IDLE ���� (Default ���)
		ONCE_RETURN,  // �ѹ� ���� Default �������
		ONCE_DESTROY, // ����Ʈ ���� ��� ���ϰ� ����������.
		TIME_RETURN,  // �����ð� ���� �ݺ��ϴ� ����Ʈ�� ���ư��� ��
		TIME_DESTROY, // ���������� �����ð� ���� ���ӵɶ� �ִϸ��̼���
	};
}