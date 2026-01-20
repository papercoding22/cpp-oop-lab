#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee
{
public:
	Employee();

	Employee(const std::string& name, const std::string& birthDate);

	virtual ~Employee();

	std::string getName() const;
	std::string getBirthDate() const;

	virtual void enterInfo();

	virtual double calculateSalary() = 0;

	virtual void describe();

protected:
	std::string name;
	std::string birthDate;
	double salary;
};

#endif // EMPLOYEE_H
