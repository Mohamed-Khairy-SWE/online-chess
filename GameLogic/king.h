#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    King(Color color, Position position)
        : Piece(color, Type::KING, position) {}

    std::vector<Position> availableMoves(const std::vector<std::vector<Piece*>>& board) const override {
        std::vector<Position> moves;

        // King can move in All 8 direction (one step each)
        const int dx[] = {-1, -1, -1,  0, 0, 1, 1, 1};
        const int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

        for (int i = 0; i < 8; ++i) {
            int newRow = position.first + dx[i];
            int newCol = position.second + dy[i];

            // Check if the new position is on the board
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                Piece* target = board[newRow][newCol];

                // Allow move if square is empty or has an enemy piece
                if (!target || target->getColor() != color) {
                    moves.emplace_back(newRow, newCol);
                }
            }
        }

        return moves;
    }
};


#endif 