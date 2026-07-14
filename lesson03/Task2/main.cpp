//
// Created by nikita on 21.06.2026.
//

#include "main.h"
#include <iostream>
struct  Counter {
    static inline int copies = 0, moves = 0;
    Counter() = default;
    Counter(const Counter&){++copies;};
    Counter(Counter&&){++moves;};
    Counter& operator= (const Counter&){++copies;};
    Counter& operator= (Counter&&) noexcept {++moves;};
};
int main() {
    Counter::copies = Counter::moves = 0;
    Counter a;
    Counter b = a;
    a = b;
    Counter c = std::move(a);
    c = std::move(b);
    std::cout << Counter::copies << " " << Counter::moves << "\n";
}