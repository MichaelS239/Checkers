#pragma once

#include <vector>

#include "move.h"

namespace checkers {

struct MovesInfo {
    std::vector<std::pair<int, int>> possible_moves;
    bool are_simple_moves;
    std::vector<std::vector<std::pair<int, int>>> path;
};

class Board {
private:
    std::vector<std::vector<char>> field_;
    bool user_color_;

    std::vector<std::pair<int, int>> CheckMove(Move move) const;

    MovesInfo GetPossibleMoves(bool user_turn, std::pair<int, int> startpoint) const;

public:
    Board() {
        field_ = std::vector<std::vector<char>>(8, std::vector<char>(8, '.'));
    }

    void Print();
    void Init(bool user_color);
    void RegisterMove(Move move);
    void CreateMove();
};

}  // namespace checkers
