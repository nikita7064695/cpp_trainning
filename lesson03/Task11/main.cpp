//
// Created by nikita on 19.07.2026.
//
struct Box {
    int* p{};
    Box(): p(new int(7)) {}
    ~Box(){delete p;}
    Box (Box&& other) noexcept : p(other.p) { other.p = nullptr; }
    Box& operator=(Box&& other) noexcept {
        if (this != &other) {
            delete p;
            p = other.p;
            other.p = nullptr;
        }
        if (p == nullptr) {    }
        return *this;
    }
};
int main() {
    Box b;
    b = std::move(b);
}