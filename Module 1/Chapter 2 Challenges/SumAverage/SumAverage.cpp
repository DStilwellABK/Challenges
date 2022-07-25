#include <iostream>
using namespace std;


int main()
{
	cout << "Please enter 3 numbers:" << endl;

	float num1 = 0, num2 = 0, num3 = 0;

	cin >> num1 >> num2 >> num3;

	float sum = num1 + num2 + num3;
	float average = sum / 3;
	cout << "Your sum is: " << sum << endl;
	cout << "Your average is: " << average << endl;
}

