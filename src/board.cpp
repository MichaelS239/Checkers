#include "board.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>

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
    return {{move.start_x, move.start_y}};
}

void Board::CreateMove() {
    std::vector<std::pair<int, int>> start_pos;
    std::vector<std::pair<int, int>> end_pos;
    for (int i = 0; i != 8; ++i) {
        for (int j = 0; j != 8; ++j) {
            if (field_[i][j] != '.' && user_color_ == (field_[i][j] == 'B')) {
                start_pos.emplace_back(i, j);
            } else if (field_[i][j] == '.') {
                end_pos.emplace_back(i, j);
            }
        }
    }
    std::vector<Move> right_moves;
    for (int i = 0; i != start_pos.size(); ++i) {
        for (int j = 0; j != end_pos.size(); ++j) {
            Move exp_move = {start_pos[i].first, start_pos[i].second, end_pos[j].first,
                             end_pos[j].second};
            try {
                CheckMove(exp_move);
            } catch (std::runtime_error err) {
                continue;
            }
            right_moves.push_back(exp_move);
        }
    }
    std::srand(std::time(0));
    int index = std::rand() % right_moves.size();
    std::vector<std::pair<int, int>> changes = CheckMove(right_moves[index]);
    for (int i = 0; i != changes.size(); ++i) {
        field_[changes[i].first][changes[i].second] = '.';
    }
    field_[right_moves[index].end_x][right_moves[index].end_y] = user_color_ ? 'B' : 'W';
}

}  // namespace checkers
