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
            Pawn *pawn = new Pawn{i == 0 ? BLACK : WHITE};
            board[i == 0 ? 1 : 6][j].setPiece(pawn);
            if (j == 0 || j == 7) {
                Rook* rook = new Rook{i == 0 ? BLACK:WHITE};
                board[i == 0 ? 0 : 7][j].setPiece(rook);
                pieces.emplace_back(std::make_unique<Rook>(*rook));
            } else if (j == 1 || j == 6) {
                Knight* knight = new Knight{i == 0 ? BLACK : WHITE};
                board[i == 0 ? 0 : 7][j].setPiece(knight);
                pieces.emplace_back(std::make_unique<Knight>(*knight));
            } else if (j == 2 || j == 5) {
                Bishop* bishop = new Bishop{i == 0 ? BLACK : WHITE};
                board[i == 0 ? 0 : 7][j].setPiece(bishop);
                pieces.emplace_back(std::make_unique<Bishop>(*bishop));
            } else if (j == 3) {
                Queen* queen = new Queen{i == 0 ? BLACK : WHITE};
                board[i == 0 ? 0 : 7][j].setPiece(queen);
                pieces.emplace_back(std::make_unique<Queen>(*queen));
            } else {
                King* king = new King{i == 0 ? BLACK : WHITE};
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

ChessBoard::ChessBoard() : NUM_ROWS{8}, NUM_COLS{8} {
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

void ChessBoard::makeMove(Point& curPos, Point& newPos, Color player) {

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
