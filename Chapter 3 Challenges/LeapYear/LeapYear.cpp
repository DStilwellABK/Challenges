#include <iostream>
using namespace std;

int main()
{
	cout << "Give a year to check if it's a leap year: " << endl;

	int year = 0;
	cin >> year;

	bool isDivisibleOf4 = year % 4 == 0;
	bool isDivisibleOf100 = year % 100 == 0;

	string result = " Is not a leap year";

	if (isDivisibleOf4) {
		if (isDivisibleOf100) {
			if (year % 400 == 0) {
				result = " Is a leap year";
			}
		}
		else {
			result = " Is a leap year";
		}
	}

	cout << year << result << endl;

}