#include "PCH.h"
#include "StudentInfo.h"

void StudentInfo::InputInfo()
{
	cout << "�̸� �Է� : ";
	cin >> cName;
	cin.clear();
	cin.ignore();
	cout << "���� ���� �Է� : ";
	iKor = InputScore();
	cout << "���� ���� �Է� : ";
	iEng = InputScore();
	cout << "���� ���� �Է� : ";
	iMath = InputScore();
}

void StudentInfo::PrintInfo()
{
	system("cls");
	cout << "�̸� : " << cName << endl;
	cout << "���� : " << iKor << "��" << endl;
	cout << "���� : " << iEng << "��" << endl;
	cout << "���� : " << iMath << "��" << endl;
	cout << "���� : " << Sum() << "��" << endl;
	cout << "��� : " << Mean() << "��" << endl;
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

		cout << "�ٽ� �Է��ϼ���." << endl;
	}
	

}
