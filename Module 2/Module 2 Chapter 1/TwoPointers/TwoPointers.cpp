#include <iostream>

using namespace std;

int main()
{
	int a;
	int b;

	cout << "Enter 2 numbers: " << endl;
	cin >> a >> b;

	int* ptrA = &a;
	int* ptrB = &b;

	cout << "PtrA: " << ptrA << endl;
	cout << "PtrB: " << ptrB << endl;
}
