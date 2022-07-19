#include <iostream>
using namespace std;

int CubeNumber(int num) {
	return num * num * num;
}
int main() {
	cout << "Please enter a number to be cubed: " << endl;

	int num = 0;
	cin >> num;

	int result = CubeNumber(num);
	cout << "Your number cubed result is: " << result << endl;
}