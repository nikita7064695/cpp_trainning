//
// Created by nikita on 19.07.2026.
//
#include <iostream>
struct Tr {
    static  inline int moves = 0;
    Tr() = default;
    Tr(Tr&&){++moves;}
};
Tr make_ok() {
    Tr t;
    return t;
}
Tr make_bad() {
    Tr t;
    return std::move(t);
}
int main() {
    Tr::moves = 0;
    Tr a = make_ok();
    std::cout << "moves after ok: " << Tr::moves << std::endl;
    Tr::moves = 0;
    Tr b = make_bad();
    std::cout << "moves after bad: " << Tr::moves << std::endl;
}