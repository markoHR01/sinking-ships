#ifndef CLIENT_H
#define CLIENT_H

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
        explicit Board(int size) : board(size * size, Token::Empty),
                                   size(size) {}

        const Token& operator()(int x, int y) const {
            return board[y * size + x];
        }

        void operator()(int x, int y, Token token) {
            board[y * size + x] = token;
        }

    private:
        std::vector<Token> board;
        int size;
};

#endif
