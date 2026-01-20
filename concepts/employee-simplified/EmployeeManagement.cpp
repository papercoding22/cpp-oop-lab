#ifndef EMPLOYEEMANAGEMENT_CPP
#define EMPLOYEEMANAGEMENT_CPP

#include <vector>
#include "OfficeEmployee.cpp"
#include "Worker.cpp"

class EmployeeManagement
{
private:
	vector<Employee *> employeeList;

public:
	EmployeeManagement()
	{
	}

	~EmployeeManagement()
	{
		for (Employee *e : employeeList)
		{
			delete e;
		}
	}

	void addEmployee(Employee *e)
	{
		employeeList.push_back(e);
	}

	void enterList()
	{
		int n;
		cout << "\n";
		cout << "========================================\n";
		cout << "       EMPLOYEE REGISTRATION SYSTEM     \n";
		cout << "========================================\n\n";

		cout << "How many employees to register? ";
		cin >> n;
		cin.ignore();
		cout << "\n";

		for (int i = 0; i < n; i++)
		{
			int type;
			Employee *e = NULL;

			cout << "----------------------------------------\n";
			cout << "          Employee #" << i + 1 << " of " << n << "\n";
			cout << "----------------------------------------\n";
			cout << "\n";
			cout << "  Select employee type:\n";
			cout << "    [1] Office Employee\n";
			cout << "    [2] Worker\n";
			cout << "\n";
			cout << "  Your choice: ";
			cin >> type;
			cin.ignore();
			cout << "\n";

			if (type == 1)
			{
				cout << "  >> Adding Office Employee\n\n";
				e = new OfficeEmployee();
			}
			else if (type == 2)
			{
				cout << "  >> Adding Worker\n\n";
				e = new Worker();
			}
			else
			{
				cout << "  [!] Invalid choice. Please try again.\n\n";
				i--;
				continue;
			}

			e->enterInfo();
			employeeList.push_back(e);

			cout << "\n  [OK] Employee registered successfully!\n\n";
		}

		cout << "========================================\n";
		cout << "   Registration Complete: " << n << " employee(s)\n";
		cout << "========================================\n\n";
	}

	void displayAll()
	{
		if (employeeList.empty())
		{
			cout << "\n";
			cout << "  +-----------------------------+\n";
			cout << "  |    No employees to show     |\n";
			cout << "  +-----------------------------+\n";
			return;
		}

		cout << "\n";
		cout << "========================================\n";
		cout << "         ALL EMPLOYEES (" << employeeList.size() << ")\n";
		cout << "========================================\n";

		for (size_t i = 0; i < employeeList.size(); i++)
		{
			cout << "\n  --- Employee #" << i + 1 << " ---";
			employeeList[i]->describe();
		}

		cout << "\n========================================\n";
		cout << "          End of List\n";
		cout << "========================================\n";
	}

	double calculateTotalSalary()
	{
		double total = 0;
		for (Employee *e : employeeList)
		{
			total += e->calculateSalary();
		}
		return total;
	}
};

#endif // EMPLOYEEMANAGEMENT_CPP
