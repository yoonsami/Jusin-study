#include "PCH.h"
#include "ReportProgram.h"
#include "StudentInfo.h"

ReportProgram::ReportProgram() : _studentScore(3)
{

}

ReportProgram::~ReportProgram()
{
	for (size_t i = 0; i < _studentScore.size(); i++)
	{
		if (_studentScore[i])
			delete _studentScore[i];
	}
	_studentScore.clear();
}

void ReportProgram::Init()
{
	system("cls");
	cout << "�л� ������ ������ �Է����ּ���." << endl;
	for (size_t i = 0; i < _studentScore.size(); ++i)
	{
		_studentScore[i] = new StudentInfo;
		_studentScore[i]->InputInfo();
	}
}

void ReportProgram::Update()
{
	while (true)
	{
		system("cls");
		cout << "1] ����ϱ�\t2] �Է��ϱ�\t3] �˻��ϱ�\t4] �����ϱ�" << endl;

		int iInput = 0;
		int iCount = 0;
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			Render();
			break;
		case 2:
			cout << "�߰��� ������ �Է��� �л� ���� �Է��ϼ���." << endl;

			cin >> iCount;
			InputInfo(iCount);
			break;
		case 3:
			Search();
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}

void ReportProgram::Render()
{
	for (size_t i = 0; i < _studentScore.size(); i++)
	{
		cout << i + 1 << "�� ° �л��� ����" << endl;
		_studentScore[i]->PrintInfo();
	}
}

void ReportProgram::InputInfo(int count)
{
	for (int i = 0; i < count; i++)
	{
		StudentInfo* tmp = new StudentInfo;
		tmp->InputInfo();
		_studentScore.push_back(tmp);
	}
}

void ReportProgram::Search()
{
	cout << "�˻��� �л��� �̸��� �Է��ϼ���." << endl;
	char c[32] = {};
	cin >> c;
	for (size_t i = 0; i < _studentScore.size(); i++)
	{
		if (strcmp(c, _studentScore[i]->GetName()) == 0)
		{
			_studentScore[i]->PrintInfo();
		}
	}
}

