#ifndef OFFICEEMPLOYEE_H
#define OFFICEEMPLOYEE_H

#include "Employee.h"
#include <string>

class OfficeEmployee : public Employee
{
public:
	OfficeEmployee();

	OfficeEmployee(const std::string& name, const std::string& birthDate, int workingDays);

	virtual ~OfficeEmployee();

	void setWorkingDays(int wds);

	double calculateSalary() override;

	void describe() override;

	void enterInfo() override;

private:
	int workingDays;
};

#endif // OFFICEEMPLOYEE_H