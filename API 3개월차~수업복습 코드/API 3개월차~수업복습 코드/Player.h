#pragma once
#include "Object.h"

class CHammer;
class CPlayer : public CObject
{
public:
   // CObject을(를) 통해 상속됨
    virtual void Init() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    void		Key_Input();
    void        Set_Player_Aim();
    
public:

private:

};

