#include "pch.h"
#include "MainGame.h"
#include "Define.h"
#include "ObjectMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "LineMgr.h"

CMainGame::CMainGame()
{

}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Init()
{
	m_DC = GetDC(g_hWnd);
	CObjectMgr::Get_Instance()->Add_Object(OT_PLAYER, CAbstractFactory<CPlayer>::Create());
	CLineMgr::Get_Instance()->Init();
}

void CMainGame::Update()
{
	CObjectMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
}

void CMainGame::Render()
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	CObjectMgr::Get_Instance()->Render(m_DC);
	CLineMgr::Get_Instance()->Render(m_DC);
}

void CMainGame::Late_Update()
{
	CObjectMgr::Get_Instance()->Late_Update();
}

void CMainGame::Release()
{
	CObjectMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_DC);
}
