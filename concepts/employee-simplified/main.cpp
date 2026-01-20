#include "EmployeeManagement.cpp"

void displayMenu()
{
	cout << "\n";
	cout << "========================================\n";
	cout << "        EMPLOYEE MANAGEMENT SYSTEM      \n";
	cout << "========================================\n";
	cout << "\n";
	cout << "  [1] Register Employees\n";
	cout << "  [2] Display All Employees\n";
	cout << "  [3] Calculate Total Salary\n";
	cout << "  [0] Exit\n";
	cout << "\n";
	cout << "  Your choice: ";
}

int main()
{
	EmployeeManagement manager;
	int choice;

	do
	{
		displayMenu();
		cin >> choice;
		cin.ignore();

		switch (choice)
		{
		case 1:
			manager.enterList();
			break;
		case 2:
			manager.displayAll();
			break;
		case 3:
			cout << "\n";
			cout << "  +-----------------------------+\n";
			cout << "  |       SALARY SUMMARY        |\n";
			cout << "  +-----------------------------+\n";
			cout << "  | Total Payroll: $" << manager.calculateTotalSalary() << "\n";
			cout << "  +-----------------------------+\n";
			break;
		case 0:
			cout << "\n";
			cout << "========================================\n";
			cout << "    Thank you for using the system!     \n";
			cout << "========================================\n";
			cout << "\n";
			break;
		default:
			cout << "\n  [!] Invalid choice. Please try again.\n";
		}
	} while (choice != 0);

	return 0;
}
