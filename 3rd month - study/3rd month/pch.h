#pragma once

#include "framework.h"


#include <list>
#include <algorithm>
#include <ctime>
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

using namespace std;