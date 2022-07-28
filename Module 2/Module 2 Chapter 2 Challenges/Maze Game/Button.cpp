#include <iostream>
#include "Button.h"

Button::Button(int x, int y, Door doorToOpen)
	: PlaceableActor(x, y)
	, m_isPressed(false)
	, m_toggable(true)
	, m_doorToOpen(doorToOpen)
	
{

}

void Button::Draw() {
	std::cout << (char)254;
}
