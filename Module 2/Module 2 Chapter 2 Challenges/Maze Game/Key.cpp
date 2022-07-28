#include <iostream>
#include <Windows.h>

#include "Key.h"

using namespace std;

void Key::Draw() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	cout << "+";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}