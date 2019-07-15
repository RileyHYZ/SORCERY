#include "chessBoard.h"
#include "point.h"
#include "color.h"
#include "exception.h"
#include <numeric>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

void ChessBoard::initPieces(Color c) {
    for(int i = 0; i < 8; i++) {
        // Initialize pawn
        pieces.emplace_back(make_unique<Pawn>(c));
        board.at(c == WHITE ? 1 : 6).at(i).setPiece(pieces.back().get());

        // Initialize piece
        if (i == 0 || i == 7) {
            pieces.emplace_back(make_unique<Rook>(c));
            board.at(c == WHITE ? 0 : 7).at(i).setPiece(pieces.back().get());
        } else if (i == 1 || i == 6) {
            pieces.emplace_back(make_unique<Knight>(c));
            board.at(c == WHITE ? 0 : 7).at(i).setPiece(pieces.back().get());    
        } else if (i == 2 || i == 5) {
            pieces.emplace_back(make_unique<Bishop>(c));
            board.at(c == WHITE ? 0 : 7).at(i).setPiece(pieces.back().get());              
        } else if (i == 3) {               
            pieces.emplace_back(make_unique<Queen>(c));
            board.at(c == WHITE ? 0 : 7).at(i).setPiece(pieces.back().get());
        } else {
            pieces.emplace_back(make_unique<King>(c));
            board.at(c == WHITE ? 0 : 7).at(i).setPiece(pieces.back().get());
        }
    }
}

void ChessBoard::initCards() {
    vector<int> rand(32);
    iota(rand.begin(), rand.end(), 1);
    auto rng = default_random_engine {};
    shuffle(rand.begin(), rand.end(), rng);

    int ind = 0;
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            if (rand[ind] < 4) {
                board[i][j].setCard(PLUSONEHP);
            } else if(rand[ind] >= 4 && rand[ind] < 7) {
                board[i][0].setCard(DESTRUCTION);
            } else if(rand[ind] >= 7 && rand[ind] < 13) {
                board[i][0].setCard(ENCHANTMENT);
            } else if(rand[ind] >= 13 && rand[ind] < 22) {
                board[i][0].setCard(BLANK);
            } else if(rand[ind] >= 22 && rand[ind] < 27) {
                board[i][0].setCard(FIRECOLUMN);
            } else if(rand[ind] >= 27 && rand[ind] < 29) {
                board[i][0].setCard(MOAT);
            } else if(rand[ind] >= 29 && rand[ind] < 31) {
                board[i][0].setCard(CURSE);
            } else {
                board[i][0].setCard(RESURRECTION);
            }
            ind++;
        }
    }
}

// Constructor

ChessBoard::ChessBoard() : NUM_ROWS{8}, NUM_COLS{8}, defaultPromotionPieces{vector<char>{2, 'q'}} {
    vector<vector<Square> > tmp;
    board = tmp;

    for (int i = 0; i < NUM_ROWS; ++i) {
        vector<Square> v;
        
        for (int j = 0; j < NUM_COLS; ++j) {
            Square s{nullptr, NONE, (i + j) % 2 == 0 ? BLACK : WHITE};
            v.emplace_back(s);
        }

        board.emplace_back(v);
    }
    initPieces(WHITE);
    initPieces(BLACK);
    initCards();
}

// Public Methods

void ChessBoard::setDefaultPromotionPiece(Color player, char piece) { 
    piece = tolower(piece);

    if (!(piece == 'q' || piece == 'r' || piece == 'b' || piece == 'n')) {
        throw InvalidDefaultPromotionPieceException();
    }

    defaultPromotionPieces.at(player) = piece;
}

void ChessBoard::makeMove(Point& curPos, Point& newPos, Color player) {
    // Check if same position
    if (curPos == newPos) throw DidNotMoveException();

    // Check for out of bounds
    if (curPos.getX() < 0 || curPos.getX() >= NUM_ROWS || curPos.getY() < 0 || curPos.getY() >= NUM_COLS
        || newPos.getX() < 0 || newPos.getX() >= NUM_ROWS || newPos.getY() < 0 || newPos.getY() >= NUM_COLS) throw OutOfBoundsException();

    ChessPiece* piece = board.at(curPos.getX()).at(curPos.getY()).getPiece();
    ChessPiece* capturedPiece = board.at(newPos.getX()).at(newPos.getY()).getPiece();

    // Check that there is a piece selected
    if (piece == nullptr) throw NoPieceSelectedException();

    // Check that the right player's piece is selected
    if (piece->getColor() != player) throw WrongPieceSelectedException();

    // Check for invalid move for that piece type
    if (!piece->checkValidMove(curPos, newPos, capturedPiece != nullptr)) throw InvalidPieceMovementException();

    // Check for blocked path
    vector<Point> v = piece->getPiecePath(curPos, newPos);
    
    for (Point p : v) {
        ChessPiece* pi = board.at(p.getX()).at(p.getY()).getPiece();
        if (pi != nullptr && (p != newPos || pi->getColor() == player)) throw BlockedPathException();
    }

    // Do the move
    board.at(curPos.getX()).at(curPos.getY()).setPiece(nullptr);

    // If King is captured, decrease HP; else move the piece
    // If piece captures the King, it's removed from the game
    if (King* k = dynamic_cast<King*>(capturedPiece)) {
        int newHP = k->getHP() - 1;
        k->setHP(newHP);
    } else {
        for (int i = 0; i < pieces.size(); ++i) {
            if (pieces.at(i).get() == capturedPiece) {
                pieces.erase(pieces.begin() + i);
                break;
            }
        }
        board.at(newPos.getX()).at(newPos.getY()).setPiece(piece);

        // Pawn promotion
        if (dynamic_cast<Pawn*>(piece) && (player == BLACK && newPos.getX() == 0 || player == WHITE && newPos.getX() == NUM_ROWS - 1)) {
            unique_ptr<ChessPiece> cp;
            switch (defaultPromotionPieces.at(player)) {
                case 'q':
                    cp = make_unique<Queen>(player);
                    break;
                case 'n':
                    cp = make_unique<Knight>(player);
                    break;
                case 'b':
                    cp = make_unique<Bishop>(player);
                    break;
                case 'r':
                    cp = make_unique<Rook>(player);
                    break;
            }
            board.at(newPos.getX()).at(newPos.getY()).setPiece(cp.get());
            pieces.push_back(move(cp));
        }
    }   
}

bool ChessBoard::checkStandstill() {
    
}

void ChessBoard::applyCardAt(Point& pos) {

}

// Iterator

ChessBoard::Iterator::Iterator(std::vector<std::vector<Square> > board, int curRow, int curCol, int numCols) \
 : board{board}, curRow{curRow}, curCol{curCol}, numCols{numCols} {}

bool ChessBoard::Iterator::operator!=(const Iterator& it) const {
    return !(curRow == it.curRow && curCol == it.curCol);
}

ChessBoard::Iterator& ChessBoard::Iterator::operator++() {
    if (curCol == numCols - 1) {
        --curRow;
        curCol = 0;
    } else {
        ++curCol;
    }

    return *this;
}

Square& ChessBoard::Iterator::operator*() {
    return board.at(curRow).at(curCol);
}

ChessBoard::Iterator ChessBoard::begin() {
    return Iterator{board, NUM_ROWS - 1, 0, NUM_COLS};
}

ChessBoard::Iterator ChessBoard::end() {
    return Iterator{board, -1, 0, NUM_COLS};
}