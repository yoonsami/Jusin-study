#pragma once

#include "Client_Defines.h"
#include "Base.h"

class CMainApp :
    public CBase
{
private:
    CMainApp();
    virtual ~CMainApp() = default;

public:
    HRESULT Init();

    void Update();
    void Render();

public:
    static CMainApp* Create();
    virtual void Free() override;
};

