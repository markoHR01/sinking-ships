#include "board.h"

Board::Board(int size)
       : board(size * size, Token::Empty),
         size_(size) {}

const Token& Board::operator()(int x, int y) const {
    return board.at(y * size_ + x);
}

void Board::operator()(int x, int y, Token token) {
    board.at(y * size_ + x) = token;
}

int Board::size() const {
    return size_;
}
