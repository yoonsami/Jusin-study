#pragma once
#include "Object.h"

class Bullet;
class Player : public Object
{
public:
	Player() :m_pBulletList(nullptr) {}
	virtual ~Player();
public:
	virtual void		Init() override;
	virtual void		Update() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;

public:
	void Set_Bullet(list<Object*>* _bulletList) { m_pBulletList = _bulletList; }
private:
	void Key_Input();
	Object* Create_Bullet(DIRECTION _dir);
	
private:
	list<Object*>* m_pBulletList;
};

