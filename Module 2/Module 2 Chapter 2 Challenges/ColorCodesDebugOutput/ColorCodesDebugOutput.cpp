// This is just to figure out which color codes go with which

#include <iostream>
#include <Windows.h>

int main()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (int i = 0; i < 300; i++)
	{
		std::cout << "Color for: " << i << std::endl;
		SetConsoleTextAttribute(console, i);
	}


	
}