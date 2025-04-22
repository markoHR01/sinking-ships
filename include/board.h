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
        explicit Board(int size)
                      : board(size * size, Token::Empty),
                        size_(size) {}

        const Token& operator()(int x, int y) const {
            return board[y * size_ + x];
        }

        void operator()(int x, int y, Token token) {
            board[y * size_ + x] = token;
        }

        int size() const { return size_; }

    private:
        std::vector<Token> board;
        int size_;
};

#endif
