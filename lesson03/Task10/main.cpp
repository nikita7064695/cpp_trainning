//
// Created by nikita on 19.07.2026.
//
#include <iostream>
template <class F, class... Args>
decltype(auto) call_forward(F&& f, Args&&... args) {
    return (f)((args)...);
}
struct Probe {
    void operator()(int&) const { std::cout << "lvalue\n";}
    void operator()(int&&) const { std::cout << "rvalue\n";}
};
int main() {
    Probe p;
    int x = 0;
    call_forward(p, x);
    call_forward(p, 0);
}