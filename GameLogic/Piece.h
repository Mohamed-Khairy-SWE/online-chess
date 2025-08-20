#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility> // we need this for std::pair, which we'll use to represent board coordinates (row , col)

// An enumaration to represent the two colors in chess
enum class PieceColor {
    WHITE,
    BLACK
};

// An enumaration for each type of piece
enum class PieceType {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

/*
 * @class Piece
 * @brief The base class for all chess pieces.
*/
class Piece {
protected:
    PieceType type;
    PieceColor color;
public:
    // A type alias for board coordinates to make the code more readable.
    using Coordinate = std::pair<int, int>;

    /*
     * @brief Constructor for the Piece class
     * @param pieceType the type of the piece (e.g., PAWN, ROOK)
     * @param pieceColer the color of the piece (WHITE or BLACK)
    */
    Piece(PieceColor pieceColor , PieceType pieceType) : type(pieceType), color(pieceColor) {}

    /*
     * @brief Virtual destructor
     * This is crucial for base classes, it ensures that when you delete a 
     * pointer to a base class, the destructor of the derived class is also called.
    */
    virtual ~Piece() = default;

    // --- Getters ---
    PieceType getType() const {return type;}
    PieceColor getColor() const { return color;}

    /*
     * @brief Gets all valid moves for this piece from a given position.
     * @param currentPosition The current coordinate of the piece on the board.
     * @param board A reference to the game board (we will define this class later)
     * @return A vector of Coordinates representing all possible legal moves.
    */
    virtual std::vector<Coordinate> getValidMoves(const Coordinate& currentPosition /*, const Board& board */) const = 0;
};

#endif 