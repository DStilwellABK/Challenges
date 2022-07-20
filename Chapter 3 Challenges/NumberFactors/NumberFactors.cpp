#include <iostream>
using namespace std;

int main()
{
	int num;
	bool validInput = false;
	do {
		cout << "Please enter a number: ";
		cin >> num;
		if (cin.fail()) {
			validInput = false;
			cin.clear();
			cin.ignore(99, '\n');
			cout << "That is not a number!" << endl;
		}
		else {
			validInput = true;
		}
	} while (!validInput);

	for (int i = 1; i <= num; i++) {
		if (num % i == 0) cout << i << endl;
	}


}
