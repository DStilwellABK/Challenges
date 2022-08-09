#include <iostream>
#include "Position.h"

Position::Position() :
	x_(0),
	y_(0)
{

}

void Position::SetPosition(int x, int y) {
	this->x_ = x;
	this->y_ = y;
}
