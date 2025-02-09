#include "checkers_game.h"

#include <iostream>
#include <stdexcept>

namespace checkers {

void CheckersGame::Start() {
    user_color_ = input_handler_.GetColor();
    board_.Init(user_color_);
    bool user_turn = user_color_;
    GameState cur_state = GameState::Game;
    while (cur_state == GameState::Game) {
        if (user_turn) {
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
        }
        user_turn = !user_turn;
        cur_state = CheckState(user_turn);
    }

    board_.Print();

    switch (cur_state) {
        case GameState::Draw:
            std::cout << "Draw!" << '\n';
            break;
        case GameState::User:
            std::cout << "User won!" << '\n';
        case GameState::Computer:
            std::cout << "Computer won!" << '\n';
        default:
            break;
    }
}

GameState CheckersGame::CheckState(bool user_turn) const {
    return GameState::Game;
}

}  // namespace checkers
