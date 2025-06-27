#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
public:
    Queen(Color color, Position position)
        : Piece(color, Type::QUEEN, position) {}

    std::vector<Position> availableMoves(const std::vector<std::vector<Piece*>>& board) const override {
        std::vector<Position> moves;

        // Queen can move in all 8 directions (multipule steps)
        const int dx[] = {-1, -1, -1,  0, 0, 1, 1, 1};
        const int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

        for (int i = 0; i < 8; i++) {
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