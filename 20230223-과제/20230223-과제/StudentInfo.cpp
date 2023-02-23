#include "PCH.h"
#include "StudentInfo.h"

void StudentInfo::InputInfo()
{
	cout << "이름 입력 : ";
	cin >> cName;
	cin.clear();
	cin.ignore();
	cout << "국어 점수 입력 : ";
	iKor = InputScore();
	cout << "영어 점수 입력 : ";
	iEng = InputScore();
	cout << "수학 점수 입력 : ";
	iMath = InputScore();
}

void StudentInfo::PrintInfo()
{
	system("cls");
	cout << "이름 : " << cName << endl;
	cout << "국어 : " << iKor << "점" << endl;
	cout << "영어 : " << iEng << "점" << endl;
	cout << "수학 : " << iMath << "점" << endl;
	cout << "총점 : " << Sum() << "점" << endl;
	cout << "평균 : " << Mean() << "점" << endl;
	system("pause");
}

int StudentInfo::InputScore()
{
	
	while (true)
	{
		int tmp;
		cin >> tmp;
		cin.clear();
		cin.ignore();

		if (tmp <= 100 && tmp >= 0)
			return tmp;

		cout << "다시 입력하세요." << endl;
	}
	

}
