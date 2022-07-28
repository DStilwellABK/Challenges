#include <iostream>
#include "Game.h"

using namespace std;

void PlayDoorClosedSound();
void PlayDoorOpenSound();
void PlayPickupKeySound();
void PlayWinSound();



int main()
{
	Game myGame;
	if (myGame.Load()) {
		while (!myGame.IsGameOver()) {
			myGame.Run();
		}
		
		if (myGame.DidUserQuit()) {
			cout << "Thanks for playing!" << endl;
		}
		else if (myGame.GetPlayerLives() < 0) {
			cout << "YOU LOSE!!!!";
		}
		else {
			cout << "YOU WON!!!" << endl;
		}

		//PlayWinSound();
	}
	else {
		cout << "Game did not load. Terminating!" << endl;
	}
}
//
//void PlayDoorClosedSound() {
//    Beep(500, 75);
//    Beep(500, 75);
//}
//
//void PlayDoorOpenSound() {
//    Beep(1397, 200);
//}
//
//void PlayPickupKeySound() {
//    Beep(1568, 200);
//}
//
//void PlayWinSound() {
//    Beep(1568, 200);
//    Beep(1568, 200);
//    Beep(1568, 200);
//    Beep(1245, 200);
//    Beep(1397, 200);
//    Beep(1397, 200);
//    Beep(1397, 200);
//    Beep(1175, 200);
//}