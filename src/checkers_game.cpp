#include "checkers_game.h"

namespace checkers {
void CheckersGame::Start() {
    user_color_ = io_handler_.GetColor();
    board_.Init(user_color_);
    if (user_color_) {
        board_.Print();
        bool legal_move = false;
        while (!legal_move) {
            Move new_move = io_handler_.GetMove();
            try {
                board_.RegisterMove(new_move);
                legal_move = true;
            } catch (std::runtime_error err) {
                io_handler_.PrintError(err.what());
            }
        }
    } else {
        board_.CreateMove();
        board_.Print();
    }
}
}  // namespace checkers
