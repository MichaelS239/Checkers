#pragma once

#include "move.h"

namespace checkers {

class InputHandler {
private:
    bool user_color_;

public:
    InputHandler() {}

    bool GetColor();
    Move GetMove();
};

}  // namespace checkers
