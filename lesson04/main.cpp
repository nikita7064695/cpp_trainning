//
// Created by nikita on 09.08.2026.
//
#include <stdexcept>
#include <utility>
#include <vector>
template <typename T>
class Vector {
public:
    Vector() = default;
    explicit Vector(size_t count) {
        if (count > 0) {
            data_ = static_cast<T*>(::operator new(sizeof(T) * count));
            size_ = count;
            for (size_t i = 0; i < size_; ++i) {
                new(data_ + i) T();
            }
        }
    };
    Vector(const Vector& other) {
        size_ = other.size_;
        if (size_ > 0) {
            data_ = static_cast<T*>(::operator new(sizeof(T) * size_));
            for (size_t i = 0; i < size_; ++i) {
                new(data_ + i) T(other.data_[i]);
            }
        }
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
            for (size_t i = size_; i > 0; --i) {
                data_[i - 1].~T();
            }
            ::operator delete(data_);
            size_ = other.size_;
            if (size_ > 0) {
                data_ = static_cast<T*>(::operator new(sizeof(T) * size_));
                for (size_t i = 0; i < size_; ++i) {
                    new(data_ + i) T(other.data_[i]);
                }
            }
        };
        return *this;
    };
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            for (size_t i = size_; i > 0; --i) {
                data_[i - 1].~T();
            }
            ::operator delete(data_);
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
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
};

int main() {
    Vector<int> v(5);
    v.at(0) = 42;
    Vector<int> v2 = v;
    Vector<int> v3 = std::move(v);
    v2 = v3;
    v = std::move(v2);
}