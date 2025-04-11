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

struct ShipPart {
    const int x, y;
    bool hit;

    ShipPart(int x, int y)
            : x(x), y(y), hit(false) {}
};

class Ship {
    public:
        Ship(const std::vector<ShipPart>& s)
            : ship(s) {}

        bool hit(int x, int y) {
            for (ShipPart& sp : ship) {
                if (sp.x == x && sp.y == y) {
                    sp.hit = true;
                    return true;
                }
            }
            return false;
        }

        int health() const {
            int sum = 0;
            for (const ShipPart& sp : ship) {
                if (sp.hit == false) {
                    sum += 1;
                }
            }
            return sum;
        }

    private:
        std::vector<ShipPart> ship;
};

#endif
