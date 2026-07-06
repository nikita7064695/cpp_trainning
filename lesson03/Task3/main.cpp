//
// Created by nikita on 21.06.2026.
//


#include <iostream>

int id(const int&){std::cout << "const&\n"; return 1;}
int id(const int&&){std::cout << "&&\n"; return 2;}
int main() {
    int x = 10;
    id(5); //&&
    id(x); //const&
    id(std::move(x)); //&&
    id(x + 1); //&&
}