//
// Created by nikita on 06.07.2026.
//
#include <vector>
struct Token {
    int* p{new int(42)};
    Token() = default;
    ~Token(){delete p;}
    Token(const Token&) = delete;
    Token& operator=(const Token&) = delete;
    Token(Token&& other) noexcept : p(other.p) {other.p = nullptr;}
    Token& operator=(Token&& other) noexcept {
        if (this != &other) {
            delete p;
            p = other.p;
            other.p = nullptr;
        }
            return *this;
    }
};
int main() {
    Token a = Token{};
    //Token b = a;
    std::vector<Token> v;
    v.push_back(Token{});
}