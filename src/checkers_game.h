#pragma once

#include "board.h"
#include "io_handler.h"

namespace checkers {

class CheckersGame {
private:
    Board board_;
    IOHandler io_handler_;
    bool user_color_;

public:
    CheckersGame() {}

    void Start();
};

}  // namespace checkers
