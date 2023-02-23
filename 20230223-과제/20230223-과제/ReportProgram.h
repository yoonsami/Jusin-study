#pragma once
#include "define.h"

class StudentInfo;
class ReportProgram
{

public:
	ReportProgram();
	~ReportProgram();

public:
	void Init();
	void Update();
	void Render();
	void InputInfo(int count);
	void Search();

private:
	
	vector<StudentInfo*> _studentScore;
};

