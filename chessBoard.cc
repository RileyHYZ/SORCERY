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
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(rand.begin(), rand.end(), default_random_engine{seed});

    int ind = 0;
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            if (rand[ind] < 4) {
                board.at(i).at(j).setCard(Card::PLUSONEHP);
            } else if(rand[ind] >= 4 && rand[ind] < 7) {
                board.at(i).at(j).setCard(Card::DESTRUCTION);
            } else if(rand[ind] >= 7 && rand[ind] < 13) {
                board.at(i).at(j).setCard(Card::ENCHANTMENT);
            } else if(rand[ind] >= 13 && rand[ind] < 22) {
                board.at(i).at(j).setCard(Card::BLANK);
            } else if(rand[ind] >= 22 && rand[ind] < 27) {
                board.at(i).at(j).setCard(Card::FIRECOLUMN);
            } else if(rand[ind] >= 27 && rand[ind] < 29) {
                board.at(i).at(j).setCard(Card::MOAT);
            } else if(rand[ind] >= 29 && rand[ind] < 31) {
                board.at(i).at(j).setCard(Card::CURSE);
            } else {
                board.at(i).at(j).setCard(Card::RESURRECTION);
            }
            ind++;
        }
    }
}

void ChessBoard::removePieceAt(Square& s) {
    if (s.getPiece() == nullptr) return;

    for (int i = 0; i < pieces.size(); ++i) {
        if (pieces.at(i).get() == s.getPiece()) {
            pieces.erase(pieces.begin() + i);
            s.setPiece(nullptr);
            break;
        }
    }
}

// Constructor

ChessBoard::ChessBoard() : NUM_ROWS{8}, NUM_COLS{8}, hp{vector<int>{2, 2}}, defaultPromotionPieces{vector<char>{2, 'q'}} {
    vector<vector<Square> > tmp;
    board = tmp;

    for (int i = 0; i < NUM_ROWS; ++i) {
        vector<Square> v;
        
        for (int j = 0; j < NUM_COLS; ++j) {
            Square s{nullptr, Card::NONE, (i + j) % 2 == 0 ? BLACK : WHITE};
            v.emplace_back(s);
        }

        board.emplace_back(v);
    }
    initPieces(WHITE);
    initPieces(BLACK);
    initCards();
}

// Accessors
vector<int> ChessBoard::getHP() {
    return hp;
}

Card ChessBoard::getCardAt(Point& p) {
    return board.at(p.getX()).at(p.getY()).getCard();
}

// Mutators

void ChessBoard::setCardAt(Point& p, Card c) {
    board.at(p.getX()).at(p.getY()).setCard(c);
}

void ChessBoard::updateHP(Color player, int amount) {
    hp.at(player) += amount;
}

void ChessBoard::setDefaultPromotionPiece(Color player, char piece) { 
    piece = tolower(piece);

    if (!(piece == 'q' || piece == 'r' || piece == 'b' || piece == 'n')) {
        throw InvalidDefaultPromotionPieceException();
    }

    defaultPromotionPieces.at(player) = piece;
}

// Public Methods

void ChessBoard::makeMove(Point& curPos, Point& newPos, Color player) {
    // Check if same position
    if (curPos == newPos) throw DidNotMoveException();

    // Check for out of bounds
    if (curPos.getX() < 0 || curPos.getX() >= NUM_ROWS || curPos.getY() < 0 || curPos.getY() >= NUM_COLS
        || newPos.getX() < 0 || newPos.getX() >= NUM_ROWS || newPos.getY() < 0 || newPos.getY() >= NUM_COLS) throw OutOfBoundsException();

    ChessPiece* piece = board.at(curPos.getX()).at(curPos.getY()).getPiece();
    ChessPiece* capturedPiece = board.at(newPos.getX()).at(newPos.getY()).getPiece();
    cout<<"type"<<piece->getType()<<endl;
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

    // If King is captured, decrease HP; else move the piece and perform pawn promotion if necessary
    // If piece captures the King, it's removed from the game
    if (dynamic_cast<King*>(capturedPiece)) {
        hp.at(player == WHITE ? BLACK : WHITE) -= 1;
        removePieceAt(board.at(curPos.getX()).at(curPos.getY()));
    } else {
        // Remove captured piece
        removePieceAt(board.at(newPos.getX()).at(newPos.getY()));

        // Move the piece
        board.at(curPos.getX()).at(curPos.getY()).setPiece(nullptr);
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

bool diagMoveIsLegal(std::vector<std::vector<Square> >& board, int i, int j, int col) {
    bool legal = false;
    Color color = board[i][j].getPiece()->getColor();
    if (j > 0 && board[i][j - 1].getPiece() != nullptr) {
        legal = board[i][j - 1].getPiece()->getColor() == color;
    }
    if (j < col - 1 && board[i][j + 1].getPiece() != nullptr) {
        return legal || board[i][j + 1].getPiece()->getColor() == color;
    }
    return legal;
}

bool ChessBoard::checkStandstill() {
    int w = 0, b = 0;
    if (pieces.size() == 4) {
        for (int i = 0; i < 4; i++) {
            if(pieces[i]->getType() == "pawn") {
                if (pieces[i]->getColor() == WHITE) w ++;
                else b ++;
            }
        }
        if (w == b == 1) {
            for (int i = 0; i < NUM_ROWS - 1; i ++) {
                for (int j = 0; j < NUM_COLS; j ++) {
                    ChessPiece *cp1 = board[i][j].getPiece();
                    ChessPiece *cp2 = board[i + 1][j].getPiece();
                    if (cp1 != nullptr && cp2 != nullptr) {
                        if (cp1->getType() == "pawn" && cp2->getType() == "pawn") {
                            return !diagMoveIsLegal(board, i, j, NUM_COLS)
                                            && !diagMoveIsLegal(board, i + 1, j, NUM_COLS);
                        }
                    }
                }
            }
        }
    }
    return false;
}

void ChessBoard::applyCardAt(Color player, Point& pos) {
    Card c = board.at(pos.getX()).at(pos.getY()).getCard();

    switch (c.getValue()) {
        case Card::FIRECOLUMN:
            {
                int increment = player == WHITE ? 1 : -1;
                int end = player == WHITE ? NUM_ROWS : -1;
                for (int i = pos.getX() + increment; i != end; i += increment) {
                    if (dynamic_cast<King*>(board.at(i).at(pos.getY()).getPiece())) {
                        hp.at(player == WHITE ? BLACK : WHITE) -= 1;
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
            for (vector<Square> &v : board) {
                for (Square &s : v) {
                    if (s.getPiece() != nullptr && s.getPiece()->getColor() == player) {
                        // Erase piece from vector and board
                        removePieceAt(s);
                    }
                }
            }
            // Reinitialize pieces for that player
            initPieces(player);
            break;
        default:
            break;
    }
}

bool ChessBoard::armyIsAlive(Color color) {
    int count = 0;
    for(std::unique_ptr<ChessPiece>& cp: pieces) {
        if(cp->getColor() == color) {
            count++;
        }
        if(count >= 2) return true;
    }
    return false;
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