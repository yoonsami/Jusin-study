#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PI			3.141592f
#define			PURE		= 0
#define			GRAVITY		0.5f
#define			DELTATIME	1.0f
#define			ELASTICITY	1.f
#define			PLAYERELASTICITY	0.f
#define			MINJMPPOW	15.f
#define			MAXJMPPOW	25.f
#define			MINFIREPOW	20.f
#define			MAXFIREPOW	45.f
#define			MINBULDAM	10.f
#define			MAXBULDAM	30.f
//플레이존 좌표값 정의
#define			PLAYZONELEFT 50
#define			PLAYZONETOP 50
#define			PLAYZONERIGHT (WINCX - 50)
#define			PLAYZONEBOTTOM (WINCY - 50)

#define			OBJ_NOEVENT 0
#define			OBJ_DEAD	1
#define			PLAYER_DEAD 2

#define			CS_REPLAY   0
#define			CS_STOP		1
#define			CS_PLAY		2

extern HWND g_hWnd;





