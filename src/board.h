#pragma once

#include <vector>

#include "move.h"

namespace checkers {

class Board {
private:
    std::vector<std::vector<char>> field_;
    bool user_color_;

    std::vector<std::pair<int, int>> CheckMove(Move move);

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
