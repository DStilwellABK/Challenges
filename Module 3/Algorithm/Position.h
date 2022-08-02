#pragma once

class Position {
public:
	char x;
	char y;
	int m_cost;
	bool m_found;

	Position(char _x, char _y, int _cost);
};