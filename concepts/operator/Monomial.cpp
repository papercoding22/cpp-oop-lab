#include <iostream>

using namespace std;

class Monomial
{

private:
	int coefficient;
	int exponent;

public:
	Monomial()
	{
		coefficient = 0;
		exponent = 0;
	}

	Monomial(int coef, int exp)
	{
		coefficient = coef;
		exponent = exp;
	}

	Monomial(int coef)
	{
		coefficient = coef;
		exponent = 0;
	}

	~Monomial() {}

	Monomial operator+(Monomial &other)
	{
		Monomial result;
		result.coefficient = this->coefficient + other.coefficient;
		result.exponent = this->exponent;
		return result;
	}

	Monomial &operator=(const Monomial &other)
	{
		if (this != &other)
		{
			this->coefficient = other.coefficient;
			this->exponent = other.exponent;
		}
		return *this;
	}

	void Print()
	{
		cout << coefficient << "x^" << exponent << endl;
	}
};

int main()
{
	Monomial A;
	Monomial B(15, 2);
	Monomial C(10);
	// A.operator=(B.operator+(C));
	// Step 1: B + C -> B.operator+(C)
	// Step 2: A = result -> A.operator=(result)
	A = B + C;
	A.Print();

	return 0;
}