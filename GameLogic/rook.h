#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Rook : public Piece {
public:
    Rook(Color color, Position position)
        : Piece(color, Type::ROOK, position) {}

    std::vector<Position> availableMoves(const std::vector<std::vector<Piece*>>& board) const override {
        std::vector<Position> moves;

        // Rook directions: up, down, left, right
        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};


        for (int i = 0; i < 4; i++) {
            int newRow = position.first;
            int newCol = position.second;

            // Keep going in one direction until we hit one of our own Pieces or the board edge
            while (true) {
                newRow += dx[i];
                newCol += dy[i];

                // Check if the new position is on the board
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8){
                    Piece* target = board[newRow][newCol];
                     // Allow move if square is empty or has an enemy piece
                    if (!target || target->getColor() != color) {
                         moves.emplace_back(newRow, newCol); 
                    }else {
                         break; // we hit one of our own Pieces
                    }
                }else {
                    break; // we hit the board edge
                }
                    

            }
        }

        return moves;
    }
};


#endif