#ifndef CHESS_UI
#define CHESS_UI

#include <QWidget>            // Base class for all Qt widgets (we inherit from QWidget)
#include <QPushButton>        // For creating clickable buttons on the board (each cell)
#include <QGridLayout>        // To layout the board in an 8x8 grid
#include <QLabel>             // For showing status messages (e.g., "Checkmate!", "White's Turn", etc.)
#include <QPixmap>            // For loading and displaying PNG images of chess pieces
#include <QMap>               // To map piece type + color to their corresponding images (QPixmap)
#include <memory>             
#include <utility>            
#include <boost/asio/ip/tcp.hpp> // For TCP networking: boost::asio::ip::tcp::socket
#include "game.h"     

class ChessWidget: public QWidget {
    Q_OBJECT /* This macro enables Qt's meta-object system (signals & slots, introspection, dynamic casting).
              * It must be added to any class that:
              *  - uses signals and slots (for event-driven programming)
              *  - needs Qt features like QObject::connect()
              *
              * Without it, your class can't send or receive signals, and the `moc` (Meta-Object Compiler) won't process it.
              *
              * Think of it like telling Qt: “This is a special class — it needs reflection, messaging, and more.”
              */

public:
    // @param: - Takes a reference to the Game logic (so the UI can interact with the game).
    //         - 'parent' is optional and used if this widget is part of a bigger widget (like a window).
    explicit ChessWidget(Game& game, QWidget* parent = nullptr);

    // This function sets the TCP socket used for communication with the server.
    // - We use std::shared_ptr so the socket can be safely shared across different parts of the program.
    void setGameSocket(std::shared_ptr<boost::asio::ip::tcp::socket> socket);

    // This function updates the board UI to match the current state of the game.
    // - For example, it updates piece positions, highlights moves, or shows messages like "Check".
    void updateDisplay();

    // Shows a text message to the user in a label (e.g., “Black’s turn”, “Checkmate!”).
    // - The message is passed as a QString, which is Qt's special string class (like std::string but Qt-friendly).
    void displayMessage(const QString& msg);

private:
    // Sets up the chess board in the UI by creating an 8x8 grid of buttons.
    // Each button represents a cell on the board that can display a piece image.
    void createBoard();

    // Loads all the PNG images (QPixmap) for each chess piece.
    // Stores them in a map for easy access later (e.g., load white bishop image, black rook image, etc.).
    void loadPieceImages();

    // Called when a player clicks on a board cell.
    // First click selects a piece; second click tries to move it.
    void handleCellClicked(int row, int col);

    // Clears all cell highlights (e.g., legal move highlights or previous selections).
    // This is used to reset the board's appearance after a move or invalid selection.
    void resetHighlights();


    // Reference to the Game logic class.
    // Used to get the current board state, check legal moves, and control player turns.
    Game& m_game;

    // TCP socket for communicating with the server.
    // Shared pointer allows safe usage from multiple parts of the code (e.g., UI and networking).
    std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;

    // UI label used to show messages to the player.
    // Examples: "White's turn", "Check", "Checkmate", "Invalid move", etc.
    QLabel* m_messageLabel;

    // Lays out the 8x8 grid of board cells (buttons) visually in the window.
    QGridLayout* m_gridLayout;

    // 2D array of buttons — one for each cell on the board.
    // We use QPushButton because it allows clicks, icons (piece images), and styling.
    QPushButton* m_cells[SIZE][SIZE];

    // Stores the position of the selected piece, if any.
    // Initialized to (-1, -1), which means no piece is currently selected.
    std::pair<int, int> m_selected = {-1, -1};

    // A Qt map (QMap) that associates a (piece type, color) pair with its PNG image (QPixmap).
    // Example: {(Type::KING, Color::WHITE)} -> white_king.png
    QMap<std::pair<Type, Color>, QPixmap> m_piecePixmaps;

};


#endif