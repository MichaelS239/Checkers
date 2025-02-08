#include "board.h"

#include <iostream>

namespace checkers {

void Board::Init(bool user_color) {
    user_color_ = user_color;

    for (int i = 0; i != 8; ++i) {
        if (i != 3 && i != 4) {
            for (int j = (i + 1) % 2; j < 8; j += 2) {
                field_[i][j] = (user_color ^ (i < 3)) ? 'W' : 'B';
            }
        }
    }
}

void Board::Print() {
    if (user_color_) {
        std::cout << " |ABCDEFGH" << '\n';
    } else {
        std::cout << " |HGFEDCBA" << '\n';
    }
    std::cout << "----------" << '\n';
    for (int i = 0; i != 8; ++i) {
        if (user_color_) {
            std::cout << 8 - i << '|';
        } else {
            std::cout << i + 1 << '|';
        }
        for (int j = 0; j != 8; ++j) {
            std::cout << field_[i][j];
        }
        std::cout << '\n';
    }
}

}  // namespace checkers
