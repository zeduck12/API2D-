#pragma once

namespace OBJ 
{
	enum E_DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_END };
	enum E_COLLIDED { COL_LEFT, COL_RIGHT, COL_TOP, COL_BOTTOM, COL_END };
}

namespace MONSTER
{
	enum E_TYPE { TYPE_NORMAL, TYPE_BOSS, TYPE_END }; // 현재 안씀.
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
		LOOP,		  // 주로 IDLE 상태 (Default 모션)
		ONCE_RETURN,  // 한번 돌고 Default 모션으로
		ONCE_DESTROY, // 이펙트 같은 경우 빵하고 없어져야함.
		TIME_RETURN,  // 일정시간 동안 반복하다 디폴트로 돌아가는 것
		TIME_DESTROY, // 버프같은거 일정시간 동안 지속될때 애니메이션이
	};
}