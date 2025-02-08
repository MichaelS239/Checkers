#include <vector>

namespace checkers {

class Board {
private:
    std::vector<std::vector<char>> field_;
    bool user_color_;

public:
    Board() {
        field_ = std::vector<std::vector<char>>(8, std::vector<char>(8, '.'));
    }

    void Print();
    void Init(bool user_color);
};

}  // namespace checkers
