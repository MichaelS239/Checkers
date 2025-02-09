#include "checkers_game.h"

#include <iostream>
#include <stdexcept>

namespace checkers {
void CheckersGame::Start() {
    user_color_ = input_handler_.GetColor();
    board_.Init(user_color_);
    if (user_color_) {
        board_.Print();
        bool legal_move = false;
        while (!legal_move) {
            Move new_move = input_handler_.GetMove();
            try {
                board_.RegisterMove(new_move);
                legal_move = true;
            } catch (std::runtime_error err) {
                std::cout << err.what() << '\n';
            }
        }
    } else {
        board_.CreateMove();
        board_.Print();
    }
}
}  // namespace checkers
