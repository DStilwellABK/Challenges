#pragma once
#include "Point.h"

class Player {
	Point m_pos;
	bool m_hasKey;


public:
	Player();
	~Player();

	int GetXPosition() { return m_pos.x; }
	int GetYPosition() { return m_pos.y; }

	int* GetXPositionPointer() { return &(m_pos.x); }
	int* GetYPositionPointer() { return &(m_pos.y); }

	void SetPosition(int x, int y);

	bool HasKey();
	void PickupKey();
	void UseKey();

	void Draw();
};