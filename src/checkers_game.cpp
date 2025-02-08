#include "checkers_game.h"

namespace checkers {
void CheckersGame::Start() {
    user_color_ = io_handler_.GetColor();
    board_.Init(user_color_);
    board_.Print();
}
}  // namespace checkers
