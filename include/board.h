#ifndef BOARD_H
#define BOARD_H

#include <vector>

enum class Token {
    Empty,
    Miss,
    PlayerShip,
    PlayerShipHit,
    EnemyShip,
};

class Board {
    public:
        explicit Board(int size);

        const Token& operator()(int x, int y) const;
        void operator()(int x, int y, Token token);

        int size() const;

    private:
        std::vector<Token> board;
        int size_;
};

#endif
