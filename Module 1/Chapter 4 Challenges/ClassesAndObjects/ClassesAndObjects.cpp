#include <iostream>
#include "Car.h"
using namespace std;

int main()
{
    Car myCar(2021, 300, "Ford");

    myCar.Display();
    myCar.Drive(200);
    myCar.Display();

}

