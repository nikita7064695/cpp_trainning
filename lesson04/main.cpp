//
// Created by nikita on 09.08.2026.
//
#include <stdexcept>
#include <utility>
#include <cassert>
template <typename T>
class Vector {
public:
    Vector() = default;
    explicit Vector(size_t count) {
        if (count == 0) return;

        T* new_data = static_cast<T*>(::operator new(sizeof(T) * count));
        size_t new_size = 0;
        try {
            for (; new_size < count; ++new_size) {
                new (new_data + new_size) T();
            }
        } catch (...) {
            for (size_t i = 0; i < new_size; ++i) {
                new_data[i].~T();
            }
            ::operator delete(new_data);
            throw;
        }
        data_ = new_data;
        size_ = count;
    };
    Vector(const Vector& other) {
        if (other.size_ == 0) return;
        T* new_data = static_cast<T*>(::operator new(sizeof(T) * other.size_));
        size_t new_size = 0;
        try {
            for (; new_size < other.size_; ++new_size) {
                new (new_data + new_size) T(other.data_[new_size]);
            }
        }catch (...) {
            for (size_t i = 0; i < new_size; ++i) {
                new_data[i].~T();
            }
            ::operator delete(new_data);
            throw;
        }
        data_ = new_data;
        size_ = other.size_;
    };
    Vector(Vector&& other) noexcept {
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    };
    ~Vector() {
        for (size_t i = size_; i > 0; --i) {
            data_[i - 1].~T();
        }
        ::operator delete(data_);
    };
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector tmp(other);
            swap(tmp);
        };
        return *this;
    };
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            swap(other);
        }
        return *this;
    };
    size_t size() const noexcept {return size_;};
    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        };
        return data_[index];
    };
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    void swap(Vector& other) noexcept {
        using std::swap;
        swap(data_, other.data_);
        swap(size_, other.size_);
    }
};

int main() {
    Vector<int> v(5);
    v.at(0) = 42;
    Vector<int> v2 = v;
    Vector<int> v3 = std::move(v);
    v2 = v3;
    v = std::move(v2);
    Vector<int> empty;
    assert(empty.size() == 0);
    Vector<int>empty2 = empty;
    assert(empty2.size() == 0);
    Vector<Vector<int>> vv(2);
    vv.at(0) =Vector<int>(3);
    Vector<Vector<int>> vv2 = vv;
    try {
        v.at(10) = 0;
        assert(false);
    }catch (const std::out_of_range&){}
}