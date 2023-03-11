#pragma once
#include "Creature.h"

class Bullet;
class Player : public Creature
{
public:
	Player() :m_pBulletList(nullptr) {}
	virtual ~Player();

public:
	virtual void		Init() override;
	virtual int			Update() override;
	virtual void		Late_Update() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;
public:
	void		Set_Bullet(list<Object*>* _bulletList) { m_pBulletList = _bulletList; }
	FLOAT		Get_JumpCharge() {return (clamp(JumpCharge, MINJMPPOW, MAXJMPPOW) - 15.f) / 10;}
	BOOL		IsSpacePressed() { return SpacePressed; }

private:
	virtual void		Get_Acc() override;
	void Key_Input();
	
private:
	list<Object*>*	m_pBulletList;
	DWORD64			bulletTime = GetTickCount64();

	Vec2			_Pin = {};
	bool			SetPin = false;
	FLOAT			RopeSize;
	FLOAT			FirstHeight;

	bool			SpacePressed = false;
	FLOAT			JumpCharge = 5.f;
	bool			RightPressed = false;
	bool			LeftPressed = false;
	bool			ZPressed = false;
	bool			XPressed = false;
	

	FLOAT			FireCharge = MINBULSIZE;
};

