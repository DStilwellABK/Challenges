// This program is for helping us figure out which key number is which when using _getch();

#include <iostream>
#include <conio.h>

int main()
{
    while (true) {
        std::cout << "Enter a key: ";

        int input = _getch();

        std::cout << std::endl;

        std::cout << "The key that you pressed gave this number: " << input << std::endl;

        std::cout << std::endl;
    }
}
