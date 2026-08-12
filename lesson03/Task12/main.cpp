//
// Created by nikita on 19.07.2026.
//
#include <cstdio>
#include <stdexcept>
struct File {
    std::FILE* f{};
    explicit File(const char* path) {
        f = std::fopen(path, "w");
        if (!f) throw std::runtime_error("open fail");
    }
    ~File() {if (f) std::fclose(f);}
    File(const File&) = delete;
    File& operator=(const File&) = delete;
    File(File&& other) noexcept : f(other.f) {other.f = nullptr;}
    File& operator=(File&& other) noexcept {
        if (this != &other) { if (f) std::fclose(f); f = other.f; other.f = nullptr; }
        return *this;
    }
};
File make_temp() {
    return File("temp.txt");
};
int main() {
    File a("out.txt");
    File b = std::move(a);
    File c = make_temp();
}