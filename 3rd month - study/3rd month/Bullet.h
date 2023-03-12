#pragma once
#include "Creature.h"

class Bullet : public Creature
{
public:
	Bullet();
	Bullet(const Bullet& bullet);
	virtual ~Bullet();

public:
	virtual void		Init() override;
	virtual int			Update() override;
	virtual void		Late_Update() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;
	virtual void		Set_Att(FLOAT Att) { if (m_bFullCharged) m_tStat.fAtt = Att * 1.5f; else m_tStat.fAtt = Att; }
public:
	void Set_FullCharged(BOOL FullCharged) { m_bFullCharged = FullCharged; }

private:
	BOOL			m_bFullCharged = false;
};

