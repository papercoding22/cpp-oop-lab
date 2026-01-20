
#include "Employee.h"
#include <iostream>

using namespace std;

Employee::Employee()
		: name("UNKNOWN"),
			birthDate("01/01/1990"),
			salary(0)
{
}

Employee::Employee(const std::string& name,
									 const std::string& birthDate)
		: name(name), birthDate(birthDate), salary(0)
{
}

Employee::~Employee() {}

string Employee::getName() const
{
	return name;
}

string Employee::getBirthDate() const
{
	return birthDate;
}

void Employee::describe()
{
	cout << "  | Name:        " << name << "\n";
	cout << "  | Birth Date:  " << birthDate << "\n";
	cout << "  | Salary:      $" << calculateSalary() << "\n";
}

void Employee::enterInfo()
{
	cout << "  Enter Name:        ";
	getline(cin, name);
	cout << "  Enter Birth Date:  ";
	getline(cin, birthDate);
}