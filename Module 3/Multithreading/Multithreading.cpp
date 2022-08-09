#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

static int heapInt = 0;

int dice1 = 0;
int dice2 = 0;

bool ShouldEndThread = false;

void Dice1() {
	while (!ShouldEndThread) {
		dice1++;
		if (dice1 > 100000) {
			dice1 = 0;
		}
	}
}

void Dice2() {
	while (!ShouldEndThread) {
		dice2++;
		if (dice2 > 100000) {
			dice2 = 0;
		}
	}
}

int main()
{
	heapInt = 1;
	cout << "Hello World!\n" << endl;
	thread Dice_thread_1(Dice1);
	thread Dice_thread_2(Dice2);

	char UserInput;

	bool DidQuit = false;
	while (!DidQuit) {
		system("cls");
		cout << "Enter any key to display the counter" << endl;

		cout << "q to Quit." << endl;
		cin >> UserInput;

		if (UserInput == 'q') {
			DidQuit = true;
			break;
		}

		cout << endl;
		
		cout << "Dice 1 gave: " << dice1 << endl << "Dice 2 gave: " << dice2 << endl;
		cout << "Enter a button to continue" << endl;
		
		cin >> UserInput;
		DidQuit = (UserInput == 'q');
	}

	// Need this to be a able to return to the main thread
	Dice_thread_1.join();
	Dice_thread_2.join();

	return 0;
}
