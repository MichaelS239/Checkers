#pragma once

#include <iostream>

#include "move.h"

namespace checkers {

class IOHandler {
private:
    bool user_color_;

public:
    IOHandler() {}

    bool GetColor();
    Move GetMove();
    void PrintError(std::string&& msg);
};

}  // namespace checkers
