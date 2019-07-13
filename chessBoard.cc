#include "chessBoard.h"
#include "point.h"
#include "color.h"
#include <numeric>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

void initPieces(std::vector<std::vector<Square> >& board,
                std::vector<std::unique_ptr<ChessPiece> >& pieces) {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 8; j++) {
            Pawn *pawn = new Pawn{i == 1 ? BLACK : WHITE};
            board[i == 0 ? 1 : 6][j].setPiece(pawn);
            if (j == 0 || j == 7) {
                Rook* rook = new Rook{i == 1 ? BLACK:WHITE};
                board[i == 0 ? 0 : 7][j].setPiece(rook);
                pieces.emplace_back(std::make_unique<Rook>(*rook));
            } else if (j == 1 || j == 6) {
                Knight* knight = new Knight{i == 1 ? BLACK : WHITE};
                board[i == 0 ? 0 : 7][j].setPiece(knight);
                pieces.emplace_back(std::make_unique<Knight>(*knight));
            } else if (j == 2 || j == 5) {
                Bishop* bishop = new Bishop{i == 1 ? BLACK : WHITE};
                board[i == 0 ? 0 : 7][j].setPiece(bishop);
                pieces.emplace_back(std::make_unique<Bishop>(*bishop));
            } else if (j == 3) {
                Queen* queen = new Queen{i == 1 ? BLACK : WHITE};
                board[i == 0 ? 0 : 7][j].setPiece(queen);
                pieces.emplace_back(std::make_unique<Queen>(*queen));
            } else {
                King* king = new King{i == 1 ? BLACK : WHITE};
                board[i == 0 ? 0 : 7][j].setPiece(king);
                pieces.emplace_back(std::make_unique<King>(*king));
            }
        }
    }
}

void initCards(std::vector<std::vector<Square> >& board) {
    std::vector<int> rand(32);
    std::iota(rand.begin(), rand.end(), 1);
    auto rng = std::default_random_engine {};
    std::shuffle(rand.begin(), rand.end(), rng);

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

ChessBoard::ChessBoard() : NUM_ROWS{8}, NUM_COLS{8}, defaultPromotionPiece{'Q'} {
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
    initPieces(board, pieces);
    initCards(board);
}

// Public Methods

void ChessBoard::setDefaultPromotionPiece(char d) {
    defaultPromotionPiece = d;
}

void ChessBoard::makeMove(Point& curPos, Point& newPos, Color player) {

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
    int w, b = 0;
    if (pieces.size() == 4) {
        for (int i = 0; i < 4; i++) {
            if(pieces[i].get()->getType() == "pawn") {
                if (pieces[i].get()->getColor() == WHITE) w ++;
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
                                            || !diagMoveIsLegal(board, i + 1, j, NUM_COLS);
                        }
                    }
                }
            }
        }
    }
    return false;
}

void ChessBoard::applyCardAt(Point& pos) {

}

bool ChessBoard::armyIsAlive(Color color) {
    int count = 0;
    for(std::unique_ptr<ChessPiece>& cp: pieces) {
        if(cp.get()->getColor() == color) {
            count++;
        }
        if(count >= 2) return true;
    }
    return false;
}

int ChessBoard::getPlayerHp(Color color) {
    King* k;
    if(color == WHITE) {
        Square sq = board[7][4];
        k = dynamic_cast<King*>(sq.getPiece());
    } else {
        Square sq = board[0][4];
        k = dynamic_cast<King*>(sq.getPiece());
    }
    return k->getHP();
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
