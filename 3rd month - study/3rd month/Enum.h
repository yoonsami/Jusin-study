#pragma once


enum class DIRECTION
{
	DIR_LEFT,
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LU,
	DIR_RU,
	DIR_END
};

enum ObjectType
{
	OT_PLAYER,
	OT_MONSTER,
	OT_BULLET,
	OT_END
};

enum UITYPE
{
	UT_HPBAR,
	UT_JUMPCHABAR,
	UT_FIRECHABAR,
	UT_END
};