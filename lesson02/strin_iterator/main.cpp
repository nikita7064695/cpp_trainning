#include <iostream>
#include <string_view>
#include <optional>
class split_iterator {
public:
    split_iterator(std::string_view str, char del) {
        stroka = str;
        delim = del;
        pos = 0;
        next = stroka.find(delim);
        if (stroka.empty()) {
            pos = std::string_view::npos;
        }
    }
    std::string_view operator *() const {
        return stroka.substr(pos, next - pos);
    };
    split_iterator& operator ++() {
        if (next == std::string_view::npos) {
            pos = std::string_view::npos;
            return *this;
        }
        pos = next + 1;
        next = stroka.find(delim, pos);
        if (pos == stroka.size() && next == std::string_view::npos) {
            return *this;
        }
        return *this;
    };
    bool operator !=(const split_iterator& other) const {
        return pos != other.pos || next != other.next;
    };
    split_iterator(): pos(std::string_view::npos), next(std::string_view::npos) {};
private:
    std::string_view stroka;
    char delim;
    size_t pos;
    size_t next;
};
int main() {
    std::string_view s = "a,,bсd,";

    split_iterator it{s, ','};   // итератор на начало
    split_iterator end{};        // итератор-конец

    for (; it != end; ++it) {
        std::cout << "[" << *it << "]";
    }
}