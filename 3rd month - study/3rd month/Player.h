#pragma once
#include "Creature.h"

class Bullet;
class Player : public Creature
{
public:
	Player();
	Player(INT _PlayerType);
	Player(const Player& player);
	virtual ~Player();

public:
	virtual void		Init() override;
	virtual int			Update() override;
	virtual void		Late_Update() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;
public:
	void		Set_Bullet(list<Object*>* _bulletList) { m_pBulletList = _bulletList; }
	FLOAT		Get_JumpChargeRatio() {return (clamp(m_fJumpCharge, MINJMPPOW, MAXJMPPOW) - MINJMPPOW) / (MAXJMPPOW-MINJMPPOW);}
	FLOAT		Get_ShootChargeRatio() {return (clamp(m_fFireCharge, MINFIREPOW, MAXFIREPOW) - MINFIREPOW) / (MAXFIREPOW - MINFIREPOW);}
	BOOL		IsJumpCharging() { return SpacePressed; }
	BOOL		IsShootCharging() { return XPressed; }
	BOOL		IsFullCharging() { return m_bFullCharged; }
	void		Set_Invincible() {	m_bInvincible = true; Set_InvincibleTimer();}
	void		Set_InvincibleTimer() { m_InvincibleTimer = GetTickCount64(); }
private:
	virtual void		Get_Acc() override;
	void Key_Input();
	
private:
	list<Object*>*	m_pBulletList = nullptr;

	/*Vec2			_Pin = {};
	bool			SetPin = false;
	FLOAT			RopeSize = 0;
	FLOAT			FirstHeight = 0;*/

	bool			SpacePressed = false;
	bool			RightPressed = false;
	bool			LeftPressed = false;
	bool			ZPressed = false;
	bool			XPressed = false;
	
	FLOAT			m_fJumpCharge = 5.f;
	FLOAT			m_fFireCharge = 5.f;

	bool			m_bFullCharged = false;
	DWORD64			m_InvincibleTimer = GetTickCount64();
	INT				m_iPlayerType;
};

