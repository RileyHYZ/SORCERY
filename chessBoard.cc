#include "chessBoard.h"
#include "point.h"
#include "color.h"
#include "exception.h"

#include <chrono>
#include <numeric>
#include <algorithm>
#include <random>
#include <vector>
#include <unordered_map>

using namespace std;

// Constructor

ChessBoard::ChessBoard(int numRows, int numCols) : NUM_ROWS{numRows}, NUM_COLS{numCols} {
    // Init board
    for (int i = 0; i < NUM_ROWS; ++i) {
        vector<Square> v;
        
        for (int j = 0; j < NUM_COLS; ++j) {
            v.emplace_back(Square{nullptr, Card::NONE, (i + j) % 2 == 0 ? Color::BLACK : Color::WHITE});
        }

        board.emplace_back(v);
    }

    // Init pieces and cards
    initPieces(Color::WHITE);
    initPieces(Color::BLACK);

    // Init card locations
    for (int i = 2; i < NUM_ROWS - 2; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            cardLocations.emplace_back(Point{i, j});
        }
    }

    // Init number of each card
    numCards = {
        make_pair(Card::PLUSONEHP, 4),
        make_pair(Card::DESTRUCTION, 3),
        make_pair(Card::ENCHANTMENT, 6),
        make_pair(Card::BLANK, 9),
        make_pair(Card::FIRECOLUMN, 5),
        make_pair(Card::MOAT, 2),
        make_pair(Card::CURSE, 2),
        make_pair(Card::RESURRECTION, 1)
    };

    initCards();

    // Init hp
    hp[Color::WHITE] = 2;
    hp[Color::BLACK] = 2;

    // Init default promotion pieces
    defaultPromotionPieces[Color::WHITE] = 'q';
    defaultPromotionPieces[Color::BLACK] = 'q';
}

// Accessors

int ChessBoard::getPlayerHP(Color color) {
    return hp.at(color);
}

// Mutators

void ChessBoard::setDefaultPromotionPiece(Color player, char piece) { 
    piece = tolower(piece);

    if (!(piece == 'q' || piece == 'r' || piece == 'b' || piece == 'n')) {
        throw InvalidDefaultPromotionPieceException();
    }

    defaultPromotionPieces.at(player) = piece;
}

// Private helper methods

void ChessBoard::initPieces(Color c) {
    for(int i = 0; i < NUM_COLS; i++) {
        // Initialize pawn
        pieces.emplace_back(make_unique<Pawn>(c));
        board.at(c == Color::WHITE ? 1 : 6).at(i).setPiece(pieces.back().get());

        // Initialize piece
        if (i == 0 || i == 7) {
            pieces.emplace_back(make_unique<Rook>(c));
            board.at(c == Color::WHITE ? 0 : 7).at(i).setPiece(pieces.back().get());
        } else if (i == 1 || i == 6) {
            pieces.emplace_back(make_unique<Knight>(c));
            board.at(c == Color::WHITE ? 0 : 7).at(i).setPiece(pieces.back().get());    
        } else if (i == 2 || i == 5) {
            pieces.emplace_back(make_unique<Bishop>(c));
            board.at(c == Color::WHITE ? 0 : 7).at(i).setPiece(pieces.back().get());              
        } else if (i == 3) {               
            pieces.emplace_back(make_unique<Queen>(c));
            board.at(c == Color::WHITE ? 0 : 7).at(i).setPiece(pieces.back().get());
        } else {
            pieces.emplace_back(make_unique<King>(c));
            board.at(c == Color::WHITE ? 0 : 7).at(i).setPiece(pieces.back().get());
        }
    }
}

void ChessBoard::initCards() {
    vector<int> rand(32);
    iota(rand.begin(), rand.end(), 0);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(rand.begin(), rand.end(), default_random_engine{seed});

    vector<Card> cardList;

    for (auto &kvp : numCards) {
        for (int i = 0; i < kvp.second; ++i) {
            cardList.push_back(kvp.first);
        }
    }

    int ind = 0;
    for (Point &p : cardLocations) {
        if (!isWithinBounds(p)) continue;
        board.at(p.getX()).at(p.getY()).setCard(cardList.at(rand[ind]));
        ind++;
    }
}

void ChessBoard::checkMakeMove(Point& curPos, Point& newPos, Color player) {
    // Check for out of bounds
    if (!isWithinBounds(curPos) || !isWithinBounds(newPos)) throw OutOfBoundsException();

    ChessPiece* piece = board.at(curPos.getX()).at(curPos.getY()).getPiece();
    ChessPiece* capturedPiece = board.at(newPos.getX()).at(newPos.getY()).getPiece();

    // Check that valid piece was selected
    if (!validPieceSelected(piece, player)) throw InvalidSquareSelectionException{};
    
    // Check if same position
    if (curPos == newPos) throw DidNotMoveException();

    // Check for invalid move for that piece type
    if (!piece->checkValidMove(curPos, newPos, capturedPiece != nullptr)) throw InvalidPieceMovementException();

    // Check for blocked path
    vector<Point> v = piece->getPath(curPos, newPos);
    
    for (Point p : v) {
        ChessPiece* pi = board.at(p.getX()).at(p.getY()).getPiece();
        if (pi != nullptr && (p != newPos || pi->getColor() == player)) throw BlockedPathException();
    }
}

bool ChessBoard::isWithinBounds(Point& pos) {
    return pos.getX() >= 0 && pos.getX() < NUM_ROWS && pos.getY() >= 0 && pos.getY() < NUM_COLS;
}

bool ChessBoard::validPieceSelected(ChessPiece* p, Color player) {
    return p != nullptr && p->getColor() == player;
}

void ChessBoard::removePieceAt(Square& s) {
    if (s.getPiece() == nullptr) return;

    for (unsigned int i = 0; i < pieces.size(); ++i) {
        if (pieces.at(i).get() == s.getPiece()) {
            pieces.erase(pieces.begin() + i);
            s.setPiece(nullptr);
            break;
        }
    }
}

// Public Interface Methods

void ChessBoard::makeMove(Point& curPos, Point& newPos, Color player) {
    checkMakeMove(curPos, newPos, player);

    // Do the move

    // If King is captured, decrease HP; else move the piece and perform pawn promotion if necessary
    // If piece captures the King, it's removed from the game
    if (dynamic_cast<King*>(board.at(newPos.getX()).at(newPos.getY()).getPiece())) {
        hp.at(player == Color::WHITE ? Color::BLACK : Color::WHITE) -= 1;
        removePieceAt(board.at(curPos.getX()).at(curPos.getY()));
    } else {
        // Remove captured piece
        removePieceAt(board.at(newPos.getX()).at(newPos.getY()));

        // Move the piece
        board.at(newPos.getX()).at(newPos.getY()).setPiece(board.at(curPos.getX()).at(curPos.getY()).getPiece());
        board.at(curPos.getX()).at(curPos.getY()).setPiece(nullptr);

        // Pawn promotion
        if (dynamic_cast<Pawn*>(board.at(newPos.getX()).at(newPos.getY()).getPiece()) && ((player == Color::BLACK && newPos.getX() == 0) || (player == Color::WHITE && newPos.getX() == NUM_ROWS - 1))) {
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
            removePieceAt(board.at(newPos.getX()).at(newPos.getY())); // Remove pawn
            board.at(newPos.getX()).at(newPos.getY()).setPiece(cp.get()); // Add new piece
            pieces.push_back(move(cp));
        }
    }   
}

bool ChessBoard::isAtStandstill() {
    int whitePawns = 0;
    int blackPawns = 0;

    if (!(pieces.size() == 4)) return false;

    // Check that only pieces left are pawn and king
    for (int i = 0; i < 4; i++) {
        if (dynamic_cast<Pawn*>(pieces.at(i).get())) pieces.at(i)->getColor() == Color::WHITE ? ++whitePawns : ++blackPawns;
        else if (!dynamic_cast<King*>(pieces.at(i).get())) return false;
    }

    // Check that there is only 1 white pawn and 1 black pawn
    if (!(whitePawns == blackPawns && whitePawns == 1)) return false;

    // Find the location of white and black pawns
    Point whitePawnLoc;
    Point blackPawnLoc;
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            ChessPiece* cp = board.at(i).at(j).getPiece();
            if (dynamic_cast<Pawn*>(cp)) cp->getColor() == Color::WHITE ? whitePawnLoc = Point{i, j} : blackPawnLoc = Point{i, j};
        }
    }

    // Pawns are in same column and black pawn is directly in front of white pawn
    if (whitePawnLoc.getY() == blackPawnLoc.getY() && whitePawnLoc.getX() + 1 == blackPawnLoc.getX()) return true;

    return false;
}

Card ChessBoard::applyCardAt(Point& pos, Color player) {
    Card card = board.at(pos.getX()).at(pos.getY()).getCard();

    switch (card.getValue()) {
        case Card::CURSE:
            --hp.at(player == Color::WHITE ? Color::BLACK : Color::WHITE);
            break;
        case Card::PLUSONEHP:
            ++hp.at(player);
            break;
        case Card::FIRECOLUMN:
            {
                int increment = player == Color::WHITE ? 1 : -1;
                int end = player == Color::WHITE ? NUM_ROWS : -1;
                for (int i = pos.getX() + increment; i != end; i += increment) {
                    if (dynamic_cast<King*>(board.at(i).at(pos.getY()).getPiece())) {
                        hp.at(player == Color::WHITE ? Color::BLACK : Color::WHITE) -= 1;
                    } else {
                        removePieceAt(board.at(i).at(pos.getY()));
                    }
                }
            }
            break;
        case Card::MOAT:
            for (int i = 0; i < NUM_COLS; ++i) {
                removePieceAt(board.at(pos.getX()).at(i));
            }
            break;
        case Card::DESTRUCTION:
            for (int i = pos.getX() - 1; i <= pos.getX() + 1; ++i) {
                if (i < 0 || i >= NUM_ROWS) continue;

                for (int j = pos.getY() - 1; j <= pos.getY() + 1; ++j) {
                    if (j < 0 || j >= NUM_COLS) continue;

                    if (!(i == pos.getX() && j == pos.getY())) removePieceAt(board.at(i).at(j));
                }
            }
            break;
        case Card::RESURRECTION:
            // Erase pieces of that color from the board
            for (vector<Square> &v : board) {
                for (Square &s : v) {
                    if (s.getPiece() != nullptr && s.getPiece()->getColor() == player) {
                        removePieceAt(s);
                    }
                }
            }

            // Remove pieces at initialization location
            for (int i = player == Color::WHITE ? 0 : 6; i < (player == Color::WHITE ? 2 : NUM_ROWS); ++i) {
                for (int j = 0; j < NUM_COLS; ++j) {
                    removePieceAt(board.at(i).at(j));
                }
            }

            // Reinitialize pieces for that player
            initPieces(player);
            break;
        default:
            break;
    }

    board.at(pos.getX()).at(pos.getY()).setCard(Card::NONE);
    return card;
}

bool ChessBoard::armyIsAlive(Color player) {
    int count = 0;

    for(std::unique_ptr<ChessPiece>& cp: pieces) {
        if (cp->getColor() == player) {
            ++count;
        }

        if (count >= 2) return true;
    }
    return false;
}

void ChessBoard::markValidMoves(Point& pos, Color player, bool valid) {
    if (!isWithinBounds(pos)) throw OutOfBoundsException{};

    ChessPiece* piece = board.at(pos.getX()).at(pos.getY()).getPiece();
    
    if (!validPieceSelected(piece, player)) throw InvalidSquareSelectionException{};

    // Get valid moves for the piece
    vector<Point> validMoves = piece->getValidMoves(pos, player, NUM_ROWS - 1, NUM_COLS - 1);
    // Mark square as valid if within bounds and is not occupied by 
    for (Point p : validMoves) {
        try {
            checkMakeMove(pos, p, player);
            board.at(p.getX()).at(p.getY()).setValid(valid);
        } catch (InvalidMoveException &e) {
            continue;
        }
    }
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