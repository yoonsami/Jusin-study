#pragma once
#include "Object.h"
class CHammer :
    public CObject
{
public:
    // CObject을(를) 통해 상속됨
    virtual void Init() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

public:
    void Set_Aim(Vec2 aim) { m_tAim = aim; }
    BOOL Is_Hanged() { return m_bHanged; }
    void Set_Pos(FLOAT X, FLOAT Y) { m_tInfo.fX = X, m_tInfo.fY = Y; }
    void Check_Line();
    POINT& Get_HangingMousePos() { return m_tHangingMouse; }

private:
    bool  m_bHanged = false;
    POINT    m_tHangingMouse = {};
};

