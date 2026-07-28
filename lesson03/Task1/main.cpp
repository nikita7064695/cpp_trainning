#include <iostream>
#include <cstring>
#include <utility>

struct Buffer {
    size_t n{};
    char* data{};
    explicit Buffer (size_t n): n(n), data(new char[n]{}) {}
    Buffer& operator=(const Buffer& buffer) {
        if (this == &buffer) return *this;
        delete[] data;
        n = buffer.n;
        if (n > 0) {
            data = new char[n];
            std::memcpy(this->data,buffer.data, buffer.n);
        }else {
            data = nullptr;
        }
        return *this;
    };
    Buffer(const Buffer& buffer) {
        n = buffer.n;
        if (n > 0) {
            data = new char[n];
            std::memcpy(this->data,buffer.data, n);
        }else {
            data = nullptr;
        }
    };
    Buffer(Buffer&& buffer) noexcept {
        n = buffer.n;
        data = buffer.data;
        buffer.n = 0;
        buffer.data = nullptr;
    };
    Buffer& operator=(Buffer&& buffer) noexcept {
        if (this == &buffer) return *this;
        delete[] data;
        n = buffer.n;
        data = buffer.data;
        buffer.n = 0;
        buffer.data = nullptr;
        return *this;
    }
    ~Buffer() {delete[] data; }
};
int main() {
    Buffer a(8);
    std::strcpy(a.data, "hello");
    Buffer b = a;
    std::cout << b.data << std::endl;
    Buffer c = std::move(a);
    std::cout << (a.data == nullptr) << std::endl;
    Buffer d(0);
    d = b;
    std::cout << d.data << std::endl;
    Buffer e(4);
    e = std::move(c);
    std::cout << e.data << std::endl;
    e = std::move(e);
}