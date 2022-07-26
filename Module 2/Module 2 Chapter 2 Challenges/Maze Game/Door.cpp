#include "Door.h"
#include <iostream>
#include <Windows.h>

Door::Door(int x, int y, int color, int closedColor)
	:PlaceableActor(x, y, color)
	, m_isOpen(false)
	, m_closedColor(closedColor)
{

}


void Door::Draw() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_isOpen) {
		SetConsoleTextAttribute(console, m_color);
	}
	else {
		SetConsoleTextAttribute(console, m_closedColor);
	}

	std::cout << "|";
	SetConsoleTextAttribute(console, kRegularColor);
}