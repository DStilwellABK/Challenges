#pragma once
#include <string>

class Car {
	// Member vars
	int m_year;
	int m_miles;
	std::string m_brand;

public:
	// Constructors
	Car();
	Car(int year, int miles, std::string brand);
	
	// Destructors
	~Car();

	// Member functions
	void Display();
	void Drive(int miles);
};
