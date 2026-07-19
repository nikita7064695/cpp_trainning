//
// Created by nikita on 19.07.2026.
//
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
int main() {
    std::vector<std::string> from = {"a", "bb", "ccc"};
    std::vector<std::string> to;
    to.assign(from.begin(), from.end());
    std::cout << "after copy: from[0]=" << from[0] << std::endl;

    std::vector<std::string> from2 = {"x", "yy", "zzz"};
    std::vector<std::string> to2;
    to2.assign(std::make_move_iterator(from2.begin()),
                std::make_move_iterator(from2.end()));
 std::cout << "after move: from2[0]=" << from2[0] << std::endl;
}