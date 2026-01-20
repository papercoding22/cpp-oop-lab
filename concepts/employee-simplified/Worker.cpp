#ifndef WORKER_CPP
#define WORKER_CPP

#include "Employee.cpp"

class Worker : public Employee
{
public:
	Worker() : Employee(), noOfProducts(0) {}

	Worker(const string& name, const string& birthDate, int noOfProducts)
		: Employee(name, birthDate), noOfProducts(noOfProducts)
	{
	}

	~Worker() {}

	void setNoOfProducts(int n)
	{
		noOfProducts = n;
	}

	double calculateSalary() override
	{
		return noOfProducts * 5000;
	}

	void describe() override
	{
		cout << "\n";
		cout << "  +-----------------------------+\n";
		cout << "  |          WORKER             |\n";
		cout << "  +-----------------------------+\n";
		Employee::describe();
		cout << "  | Products:    " << noOfProducts << "\n";
		cout << "  +-----------------------------+\n";
	}

	void enterInfo() override
	{
		cout << "  +----- Enter Employee Info -----+\n";
		cout << "\n";
		Employee::enterInfo();
		cout << "  Enter No. of Products: ";
		cin >> noOfProducts;
		cin.ignore();
		cout << "\n";
		cout << "  +-------------------------------+\n";
	}

private:
	int noOfProducts;
};

#endif // WORKER_CPP
