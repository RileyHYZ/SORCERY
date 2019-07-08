#include <vector>

#include "chessBoard.h"
#include "point.h"
#include "color.h"
#include <numeric>
#include <algorithm>
#include <random>

void initPawns(Color color, std::vector<std::vector<Square> >& board,
                std::vector<std::unique_ptr<ChessPiece> >& pieces) {
    std::vector<Square> boardRow;
    for(int i = 0; i < 8; i++) {
        Pawn pawn{color};
        Square sq{&pawn, NONE, color};
        boardRow.emplace_back(sq);
        pieces.emplace_back(std::make_unique<Pawn>(pawn));
    }
    board.emplace_back(boardRow);
}

void initPieces(Color color, std::vector<std::vector<Square> >& board,
                std::vector<std::unique_ptr<ChessPiece> >& pieces) {
    std::vector<Square> boardRow;
    for(int i = 0; i < 8; i++) {
        if (i == 0 || i == 7) {
            Rook rook{color};
            Square sq {&rook, NONE, color};
            boardRow.emplace_back(sq);
            pieces.emplace_back(std::make_unique<Rook>(rook));
        } else if (i == 1 || i == 6) {
            Knight knight{color};
            Square sq {&knight, NONE, color};
            boardRow.emplace_back(sq);
            pieces.emplace_back(std::make_unique<Knight>(knight));
        } else if (i == 2 || i == 5) {
            Bishop bishop{color};
            Square sq {&bishop, NONE, color};
            boardRow.emplace_back(sq);
            pieces.emplace_back(std::make_unique<Bishop>(bishop));
        } else if (i == 3) {
            Queen queen{color};
            Square sq {&queen, NONE, color};
            boardRow.emplace_back(sq);
            pieces.emplace_back(std::make_unique<Queen>(queen));
        } else {
            King king{color};
            Square sq {&king, NONE, color};
            boardRow.emplace_back(sq);
            pieces.emplace_back(std::make_unique<King>(king));
        }
    }
    board.emplace_back(boardRow);
}

void initCards(std::vector<std::vector<Square> >& board) {
    std::vector<int> rand(32);
    std::iota(rand.begin(), rand.end(), 1);
    auto rng = std::default_random_engine {};
    std::shuffle(rand.begin(), rand.end(), rng);

    int ind = 0;
    std::vector<Square> cards;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 8; i++) {
            if (rand[ind] < 4) {
                Square sq{nullptr, PLUSONEHP, UNDEF};
                cards.emplace_back(sq);
            } else if(rand[ind] >= 4 && rand[ind] < 7) {
                Square sq{nullptr, DESTRUCTION, UNDEF};
                cards.emplace_back(sq);
            } else if(rand[ind] >= 7 && rand[ind] < 13) {
                Square sq{nullptr, ENCHANTMENT, UNDEF};
                cards.emplace_back(sq);
            } else if(rand[ind] >= 13 && rand[ind] < 22) {
                Square sq{nullptr, BLANK, UNDEF};
                cards.emplace_back(sq);
            } else if(rand[ind] >= 22 && rand[ind] < 27) {
                Square sq{nullptr, FIRECOLUMN, UNDEF};
                cards.emplace_back(sq);
            } else if(rand[ind] >= 27 && rand[ind] < 29) {
                Square sq{nullptr, MOAT, UNDEF};
                cards.emplace_back(sq);
            } else if(rand[ind] >= 29 && rand[ind] < 31) {
                Square sq{nullptr, CURSE, UNDEF};
                cards.emplace_back(sq);
            } else {
                Square sq{nullptr, RESURRECTION, UNDEF};
                cards.emplace_back(sq);
            }
        }
        board.emplace_back(cards);
        cards.clear();
    }
}

using namespace std;

// Constructor

ChessBoard::ChessBoard() : NUM_ROWS{8}, NUM_COLS{8} {
    initPieces(WHITE, board, pieces);
    initPawns(WHITE, board, pieces);
    initCards(board);
    initPawns(BLACK, board, pieces);
    initPieces(BLACK, board, pieces);
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