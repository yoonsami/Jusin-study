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
	cout << "학생 세명의 성적을 입력해주세요." << endl;
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
		cout << "1] 출력하기\t2] 입력하기\t3] 검색하기\t4] 종료하기" << endl;

		int iInput = 0;
		int iCount = 0;
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			Render();
			break;
		case 2:
			cout << "추가로 정보를 입력할 학생 수를 입력하세요." << endl;

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
		cout << i + 1 << "번 째 학생의 정보" << endl;
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
	cout << "검색할 학생의 이름을 입력하세요." << endl;
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

