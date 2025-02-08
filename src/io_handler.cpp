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

    return c == 'W';
}
}  // namespace checkers
