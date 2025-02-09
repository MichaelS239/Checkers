#pragma once

#include "board.h"
#include "input_handler.h"

namespace checkers {

class CheckersGame {
private:
    Board board_;
    InputHandler input_handler_;
    bool user_color_;

public:
    CheckersGame() {}

    void Start();
};

}  // namespace checkers
