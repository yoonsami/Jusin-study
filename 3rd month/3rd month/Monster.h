#pragma once
#include "Object.h"
class Monster :  public Object
{
public:
	Monster();
	virtual ~Monster();

public:
	virtual void		Init() override;
	virtual int			Update() override;
	virtual void		Late_Update() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;

private:
	void Move();
	void Turn();
	void CheckCollide();
public:
	void Set_Bullet(list<Object*>* _bulletList) { m_pBulletList = _bulletList; }

private:
	list<Object*>* m_pBulletList = nullptr;
	DWORD64			m_dwTime = GetTickCount64();
};

