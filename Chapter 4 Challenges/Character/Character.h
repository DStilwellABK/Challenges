#pragma once
#include <iostream>
class Character {
public:
	//virtual void Draw() {
	//	std::cout << "I'm not sure how to draw myself" << std::endl;
	//}
	virtual void Draw() = 0;
};

class Player : public Character {
public:
	void Draw() override {
		std::cout << "@" << std::endl;
	}
};

class Enemy : public Character {
public:
	void Draw() override {
		std::cout << "*" << std::endl;
	}
};