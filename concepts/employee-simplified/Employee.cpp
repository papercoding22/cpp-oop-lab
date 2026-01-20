#ifndef EMPLOYEE_CPP
#define EMPLOYEE_CPP

#include <iostream>
#include <string>

using namespace std;

class Employee
{
public:
	Employee()
		: name("UNKNOWN"),
		  birthDate("01/01/1990"),
		  salary(0)
	{
	}

	Employee(const string& name, const string& birthDate)
		: name(name), birthDate(birthDate), salary(0)
	{
	}

	virtual ~Employee() {}

	string getName() const
	{
		return name;
	}

	string getBirthDate() const
	{
		return birthDate;
	}

	virtual void enterInfo()
	{
		cout << "  Enter Name:        ";
		getline(cin, name);
		cout << "  Enter Birth Date:  ";
		getline(cin, birthDate);
	}

	virtual double calculateSalary() = 0;

	virtual void describe()
	{
		cout << "  | Name:        " << name << "\n";
		cout << "  | Birth Date:  " << birthDate << "\n";
		cout << "  | Salary:      $" << calculateSalary() << "\n";
	}

protected:
	string name;
	string birthDate;
	double salary;
};

#endif // EMPLOYEE_CPP
