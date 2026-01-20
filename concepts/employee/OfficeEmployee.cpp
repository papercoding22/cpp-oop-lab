#include "OfficeEmployee.h"
#include <iostream>

using namespace std;

OfficeEmployee::OfficeEmployee() : Employee(), workingDays(0) {}

OfficeEmployee::OfficeEmployee(const std::string& name, const std::string& birthDate, int workingDays) 
	: Employee(name, birthDate), workingDays(workingDays)
{
}

OfficeEmployee::~OfficeEmployee() {}

void OfficeEmployee::setWorkingDays(int wds)
{
	workingDays = wds;
}

double OfficeEmployee::calculateSalary()
{
	return workingDays * 1000;
}

void OfficeEmployee::describe()
{
	cout << "\n";
	cout << "  +-----------------------------+\n";
	cout << "  |      OFFICE EMPLOYEE        |\n";
	cout << "  +-----------------------------+\n";
	Employee::describe();
	cout << "  | Working Days: " << workingDays << "\n";
	cout << "  +-----------------------------+\n";
}

void OfficeEmployee::enterInfo()
{
	cout << "  +----- Enter Employee Info -----+\n";
	cout << "\n";
	Employee::enterInfo();
	cout << "  Enter Working Days: ";
	cin >> workingDays;
	cin.ignore();
	cout << "\n";
	cout << "  +-------------------------------+\n";
}