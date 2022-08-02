#include <iostream>
#include "Position.h"

Position::Position(char _x, char _y, int _cost) :
	x(_x),
	y(_y),
	m_cost(_cost),
	m_found(false)
{

}