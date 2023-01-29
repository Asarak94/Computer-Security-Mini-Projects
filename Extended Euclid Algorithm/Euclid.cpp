#include <iostream>
using namespace std;

// Function for extended Euclidean Algorithm
//pass a and b values as pointers
int extendedEuclid(int u, int v, int *a, int *b)
{
	// if one of the value is zero, then other value will be the gcd by default
	if (u == 0)
	{
		*a = 0;
		*b = 1;
		return v;
	}

	// Assign Temp values from recursive call
	int p1, q1; 
	// Recursive call for the extendedEuclid
	int gcd = extendedEuclid(v%u, u, &p1, &q1);

	// Update a and b
	*a = q1 - (v/u) * p1;
	*b = p1;
	return gcd;
}

int main()
{
	//Define a,b and assign u and v values
	int a, b, u = 612898, v = 765051;
	int c = extendedEuclid(u, v, &a, &b);
	cout << "a = "<<a<< endl;
	cout << "b = "<<b<< endl;
	cout << "c = "<<"GCD(" << u << ", " << v<< ") = " << c << endl;
	return 0;
}
