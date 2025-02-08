#include "board.h"

#include <exception>
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

void Board::RegisterMove(Move move) {
    char start_char = field_[move.start_x][move.start_y];
    if (start_char == '.') {
        throw std::runtime_error("Error: no figure on start position");
    }
    if ((start_char == 'W') != user_color_) {
        throw std::runtime_error("Error: wrong figure on start position");
    }
    char end_char = field_[move.end_x][move.end_y];
    if (end_char != '.') {
        throw std::runtime_error("Error: end position is not empty");
    }

    std::vector<std::pair<int, int>> changes;
    try {
        changes = CheckMove(move);
    } catch (std::runtime_error err) {
        throw err;
    }
    for (int i = 0; i != changes.size(); ++i) {
        field_[changes[i].first][changes[i].second] = '.';
    }
    field_[move.end_x][move.end_y] = user_color_ ? 'W' : 'B';
}

std::vector<std::pair<int, int>> Board::CheckMove(Move move) {
    return {};
}

}  // namespace checkers
