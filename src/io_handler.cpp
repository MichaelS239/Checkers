#include "io_handler.h"

#include <iostream>

namespace checkers {
bool IOHandler::GetColor() {
    std::cout << "Enter your color - White (W) or Black (B):" << '\n';
    char c;
    std::cin >> c;
    while (c != 'W' && c != 'B') {
        std::cout << "Enter W or B:" << '\n';
        std::cin >> c;
    }
    user_color_ = (c == 'W');

    return user_color_;
}

Move IOHandler::GetMove() {
    std::cout << "Enter your move with start and end positions (e.g. A6 B5):" << '\n';
    std::string s, t;
    std::cin >> s >> t;
    while (s.size() != 2 || t.size() != 2 || s[0] < 'A' || s[0] > 'H' || t[0] < 'A' || t[0] > 'H' ||
           s[1] < '1' || s[1] > '8' || t[1] < '1' || t[1] > '8' || s == t) {
        std::cout << "Wrong move format. Enter your move with start and end positions (e.g. A6 B5):"
                  << '\n';
        std::cin >> s >> t;
    }
    Move move;
    if (user_color_) {
        move = {7 - (s[1] - '1'), s[0] - 'A', 7 - (t[1] - '1'), t[0] - 'A'};
    } else {
        move = {s[1] - '1', 7 - (s[0] - 'A'), t[1] - '1', 7 - (t[0] - 'A')};
    }
    return move;
}

void IOHandler::PrintError(std::string&& msg) {
    std::cout << msg << '\n';
}

}  // namespace checkers
