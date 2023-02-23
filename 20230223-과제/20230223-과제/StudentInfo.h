#pragma once
class StudentInfo
{
public:
	StudentInfo() : cName{}, iKor(0), iEng(0), iMath(0)
	{

	}


public:
	void	InputInfo();
	void	PrintInfo();
	int		Sum() { return iKor + iEng + iMath; }
	float	Mean() { return Sum() / 3.f; }
	char*	GetName() { return cName; }
	int		InputScore();
private:
	char	cName[32];
	int		iKor;
	int		iEng;
	int		iMath;

};