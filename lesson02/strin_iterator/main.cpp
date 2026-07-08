#include <iostream>
#include <string_view>
#include <cassert>
#include <optional>
#include <vector>

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
void split_iterator_test(const std::string_view& input, char del, const std::vector<std::string>& expected){
    std::vector<std::string> result;
    for (auto it = split_iterator(input, del); it != split_iterator(); ++it) {
        result.push_back(std::string(*it));
    }
    assert(result == expected);
    std::cout << "Test passed" << std::endl;
};
int main() {
    std::string_view s = "a,,bсd,";
    std::string_view a = "";
    std::string_view b = "aaa";
    std::string_view c = "abcd,";
    std::string_view d = ",,,,cdv";
    std::string_view e = ",acdok";
    split_iterator_test(a, ',', {});
    split_iterator_test(b, ',', {"aaa"});
    split_iterator_test(c, ',', {"abcd", ""});
    split_iterator_test(d, ',', {"","","","","cdv"});
    split_iterator_test(e, ',',{"", "acdok"});
    split_iterator it{s, ','};   // итератор на начало
    split_iterator end{};        // итератор-конец

    for (; it != end; ++it) {
        std::cout << "[" << *it << "]";
    }
}