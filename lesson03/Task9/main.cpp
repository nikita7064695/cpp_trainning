//
// Created by nikita on 19.07.2026.
//
#include <iostream>
struct W {
    static inline int copies = 0, moves = 0;
    W() = default;
    W(const W &) {++copies;};
    W(W&&) noexcept {++moves;}
};
int main() {
    const W cw;
    W x = std::move(cw);
    std::cout << "copies=" << W::copies << " moves=" << W::moves << std::endl;
}