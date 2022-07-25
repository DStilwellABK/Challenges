#include "Car.h"
#include <iostream>

using namespace std;

// Constructors
Car::Car() 
	: m_year(2022)
	, m_miles(0)
	, m_brand("Unspecified")
{

}

Car::Car(int year, int miles, std::string brand) 
	: m_year(year)
	, m_miles(miles)
	, m_brand(brand)
{

}

// Destructors
Car::~Car() {

}

// Member functions
void Car::Display() {
	cout << "Brand: " << m_brand << endl;
	cout << "Miles: " << m_miles << endl;
	cout << "Year: " << m_year << endl;
}
void Car::Drive(int miles) {
	m_miles += miles;
}