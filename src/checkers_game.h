#pragma once

#include "board.h"
#include "game_state.h"
#include "input_handler.h"

namespace checkers {

class CheckersGame {
private:
    Board board_;
    InputHandler input_handler_;
    bool user_color_;

    GameState CheckState(bool user_turn) const;

public:
    CheckersGame() {}

    void Start();
};

}  // namespace checkers
