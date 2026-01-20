#ifndef OFFICEEMPLOYEE_CPP
#define OFFICEEMPLOYEE_CPP

#include "Employee.cpp"

class OfficeEmployee : public Employee
{
public:
	OfficeEmployee() : Employee(), workingDays(0) {}

	OfficeEmployee(const string& name, const string& birthDate, int workingDays)
		: Employee(name, birthDate), workingDays(workingDays)
	{
	}

	virtual ~OfficeEmployee() {}

	void setWorkingDays(int wds)
	{
		workingDays = wds;
	}

	double calculateSalary() override
	{
		return workingDays * 1000;
	}

	void describe() override
	{
		cout << "\n";
		cout << "  +-----------------------------+\n";
		cout << "  |      OFFICE EMPLOYEE        |\n";
		cout << "  +-----------------------------+\n";
		Employee::describe();
		cout << "  | Working Days: " << workingDays << "\n";
		cout << "  +-----------------------------+\n";
	}

	void enterInfo() override
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

private:
	int workingDays;
};

#endif // OFFICEEMPLOYEE_CPP
