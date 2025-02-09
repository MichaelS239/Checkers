#include "board.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <utility>

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
        throw;
    }
    for (int i = 0; i != changes.size(); ++i) {
        field_[changes[i].first][changes[i].second] = '.';
    }
    field_[move.end_x][move.end_y] = user_color_ ? 'W' : 'B';
}

MovesInfo Board::GetPossibleMoves(bool user_turn, std::pair<int, int> startpoint) const {
    auto const& [start_x, start_y] = startpoint;

    std::queue<std::pair<int, int>> q;
    q.emplace(start_x, start_y);
    std::vector<std::vector<bool>> used(8, std::vector<bool>(8));
    used[start_x][start_y] = true;
    std::vector<std::vector<std::pair<int, int>>> path =
            std::vector<std::vector<std::pair<int, int>>>(
                    8, std::vector<std::pair<int, int>>(8, {-1, -1}));
    std::vector<std::pair<int, int>> endpoints;
    std::vector<std::pair<int, int>> moves;
    if ((user_turn && start_x >= 1) || (!user_turn && start_x <= 6)) {
        int new_x = user_turn ? start_x - 1 : start_x + 1;
        if (start_y >= 1 && field_[new_x][start_y - 1] == '.') {
            moves.emplace_back(new_x, start_y - 1);
        }
        if (start_y <= 6 && field_[new_x][start_y + 1] == '.') {
            moves.emplace_back(new_x, start_y + 1);
        }
    }
    std::vector<std::pair<int, int>> options = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    while (!q.empty()) {
        auto const& [cur_x, cur_y] = q.front();
        q.pop();
        bool has_moves = false;
        for (int i = 0; i != 4; ++i) {
            if (cur_x + 2 * options[i].first >= 0 && cur_x + 2 * options[i].first <= 7 &&
                cur_y + 2 * options[i].second >= 0 && cur_y + 2 * options[i].second <= 7) {
                int eat_x = cur_x + options[i].first;
                int eat_y = cur_y + options[i].second;
                int new_x = cur_x + 2 * options[i].first;
                int new_y = cur_y + 2 * options[i].second;
                if (field_[eat_x][eat_y] != '.' &&
                    ((field_[eat_x][eat_y] == 'B') == user_color_) == user_turn &&
                    field_[new_x][new_y] == '.' && !used[eat_x][eat_y] && !used[new_x][new_y]) {
                    q.emplace(new_x, new_y);
                    has_moves = true;
                    used[eat_x][eat_y] = true;
                    used[new_x][new_y] = true;
                    path[new_x][new_y] = {cur_x, cur_y};
                }
            }
        }
        if (!has_moves && (cur_x != start_x || cur_y != start_y)) {
            endpoints.emplace_back(cur_x, cur_y);
        }
    }

    if (endpoints.empty()) return {std::move(moves), true, {}};
    return {std::move(endpoints), false, std::move(path)};
}

std::vector<std::pair<int, int>> Board::CheckMove(Move move) const {
    bool user_turn = (field_[move.start_x][move.start_y] == 'W') == user_color_;
    bool is_simple_move = false;

    if (field_[move.start_x][move.start_y] != '.' &&
        ((field_[move.start_x][move.start_y] == 'W') == user_color_) == user_turn &&
        field_[move.end_x][move.end_y] == '.' && std::abs(move.start_y - move.end_y) == 1) {
        if ((user_turn && move.start_x - move.end_x == 1) ||
            (!user_turn && move.start_x - move.end_x == -1)) {
            is_simple_move = true;
        }
    }

    std::pair<int, int> startpoint = {move.start_x, move.start_y};
    std::pair<int, int> endpoint = {move.end_x, move.end_y};
    if (is_simple_move) {
        std::vector<std::pair<int, int>> startpoints;
        for (int i = 0; i != 8; ++i) {
            for (int j = 0; j != 8; ++j) {
                if (field_[i][j] != '.' && ((field_[i][j] == 'W') == user_color_) == user_turn) {
                    startpoints.emplace_back(i, j);
                }
            }
        }
        for (auto const& startpoint : startpoints) {
            auto const& [possible_moves, are_simple_moves, path] =
                    GetPossibleMoves(user_turn, startpoint);
            if (!are_simple_moves) {
                throw std::runtime_error("Error: you must capture opponent's piece");
            }
        }
        return {startpoint};
    }

    auto const& [possible_moves, are_simple_moves, path] = GetPossibleMoves(user_turn, startpoint);
    if (std::find(possible_moves.begin(), possible_moves.end(), endpoint) == possible_moves.end()) {
        throw std::runtime_error("Error: illegal move");
    }

    std::vector<std::pair<int, int>> changes;
    std::pair<int, int> cur_point = endpoint;
    while (cur_point != startpoint) {
        std::pair<int, int> prev_point = path[cur_point.first][cur_point.second];
        std::pair<int, int> eat_point = {(prev_point.first + cur_point.first) / 2,
                                         (prev_point.second + cur_point.second) / 2};
        changes.push_back(std::move(eat_point));
        cur_point = prev_point;
    }
    changes.push_back(std::move(startpoint));
    return changes;
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
