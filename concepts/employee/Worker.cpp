#include "Worker.h"
#include <iostream>

using namespace std;

Worker::Worker() : Employee(), noOfProducts(0) {}

Worker::Worker(const std::string& name, const std::string& birthDate, int n) 
	: Employee(name, birthDate), noOfProducts(n)
{
}

Worker::~Worker() {}

void Worker::setNoOfProducts(int n)
{
	noOfProducts = n;
}

double Worker::calculateSalary()
{
	return noOfProducts * 5000;
}

void Worker::describe()
{
	cout << "\n";
	cout << "  +-----------------------------+\n";
	cout << "  |          WORKER             |\n";
	cout << "  +-----------------------------+\n";
	Employee::describe();
	cout << "  | Products:    " << noOfProducts << "\n";
	cout << "  +-----------------------------+\n";
}

void Worker::enterInfo()
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