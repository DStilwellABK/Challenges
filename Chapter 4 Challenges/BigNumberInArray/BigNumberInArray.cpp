

#include <iostream>
using namespace std;

int main()
{
	int numbers[5];

	// Allow the user to choose which numbers to put in.
	cout << "This program will choose the biggest number out of 5 numbers you give it." << endl;
	cout << "Please enter 5 numbers and hit entering each number: ";
	for (int i = 0; i < 5; i++)
	{
		cin >> numbers[i];
	}

	// Set a starting number as the highest.
	int biggestNumber = numbers[0];

	// For each number in the numbers array
	for (int number : numbers)
	{
		// if number is bigger than our current contender, set that as the new champion.
		if (number > biggestNumber) biggestNumber = number;
	}

	cout << "The biggest number is: " << biggestNumber << endl;
}

