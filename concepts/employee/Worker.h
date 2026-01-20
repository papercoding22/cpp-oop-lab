#ifndef WORKER_H
#define WORKER_H

#include "Employee.h"
#include <string>

class Worker : public Employee
{
private:
	int noOfProducts;

public:
	Worker();

	Worker(const std::string& name, const std::string& birthDate, int noOfProducts);

	~Worker();

	void setNoOfProducts(int n);

	double calculateSalary() override;

	void describe() override;

	void enterInfo() override;
};

#endif // WORKER_H