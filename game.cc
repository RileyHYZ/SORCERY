#include "game.h"
#include "keyboardController.h"
#include "windowController.h"
#include "textView.h"
#include "graphicalView.h"
#include "exception.h"
#include "chessBoard.h"
#include "color.h"
#include "card.h"

#include <memory>
#include <sstream>

using namespace std;

// Constructor
    
Game::Game(bool textOnly, bool graphicOnly, bool enhancementsOn, istream& in, int numRows, int numCols) : NUM_ROWS{numRows}, NUM_COLS{numCols}, 
    chessBoard{make_unique<ChessBoard>(numRows, numCols)}, curPlayer{Color::WHITE}, cardApplied{Card::NONE} {   
    if (!graphicOnly) {
        addController(move(make_unique<KeyboardController>(enhancementsOn, in)));
        addView(move(make_unique<TextView>(*this, numRows, numCols)));
    }
    if (!textOnly) {
        unique_ptr<GraphicalView> g = make_unique<GraphicalView>(*this, numCols);
        addController(move(make_unique<WindowController>(g->getWindow(), enhancementsOn)));
        addView(move(g));
    }
}

// Accessors

ChessBoard* Game::getChessBoard() {
    return chessBoard.get();
}

Card Game::getCardApplied() {
    return cardApplied;
}

// Private Methods

bool Game::playTurn(Point& curPos, Point& newPos) {
    chessBoard->makeMove(curPos, newPos, curPlayer);
    cardApplied = chessBoard->applyCardAt(newPos, curPlayer);

    // Notify observers to display screen
    displayViews();

    // Check for winner
    bool gameEnded = checkWin();

    // Switch turn if ENCHANTMENT card not applied
    if (!(cardApplied == Card::ENCHANTMENT)) curPlayer = curPlayer == Color::WHITE ? Color::BLACK : Color::WHITE;

    // Reset card applied
    cardApplied = Card::NONE;

    return gameEnded;
}

bool Game::checkWin() {
    Color opponent = curPlayer == Color::WHITE ? Color::BLACK : Color::WHITE;

    if (chessBoard->getPlayerHP(opponent) <= 0 || !chessBoard->armyIsAlive(opponent)) {
        displayMessage("The " + curPlayer.getName() + " player wins!");
        return true;
    }

    if (chessBoard->isAtStandstill()) {
        if (chessBoard->getPlayerHP(opponent) > chessBoard->getPlayerHP(curPlayer)) {
            displayMessage("The " + opponent.getName() + " player wins!");
        } else if (chessBoard->getPlayerHP(curPlayer) > chessBoard->getPlayerHP(opponent)) {
            displayMessage("The " + curPlayer.getName() + " player wins!");
        } else {
            displayMessage("It's a tie!");
        }
        return true;
    }
    
    return false;
}

void Game::showValidMoves(Point& pos) {
    chessBoard->markValidMoves(pos, curPlayer, true);
    displayViews();
    chessBoard->markValidMoves(pos, curPlayer, false);
} 

void Game::restart() {
    chessBoard = make_unique<ChessBoard>(NUM_ROWS, NUM_COLS);
    curPlayer = Color::WHITE;
    cardApplied = Card::NONE;
    displayViews();
}

// Public Interface Methods

void Game::start() {
    displayViews(); // Initial display

    string str;

    Command cmd;

    while (cin) {
        try{
            cmd = getCommand();
        } catch (InvalidCommandException& e) {
            displayMessage(e.what());
        }

        if (cmd == Command::QUIT) {
            break;
        } else if (cmd == Command::NONE) {
            continue;
        } else if (cmd == Command::MOVE) {
            Point curPos = getPoint();
            Point newPos = getPoint();
            int end;

            try {
                end = playTurn(curPos, newPos);
                if (end) break;
            } catch (InvalidMoveException& e) {
                displayMessage(e.what());
            }
        } else if (cmd == Command::RESTART) {
            restart();
        } else if (cmd == Command::DEFAULTPROMOTION) {
            char piece = getPromotPiece();
            
            try {
                cout<<"SELECTED   "<<piece<<endl;
                chessBoard->setDefaultPromotionPiece(curPlayer, piece);
            } catch (InvalidDefaultPromotionPieceException& e) {
                displayMessage(e.what());
            }
        } else if (cmd == Command::VALIDMOVES) {
            Point pos = getPoint();
            
            try {
                showValidMoves(pos);
            } catch (InvalidMoveException& e) {
                displayMessage(e.what());
            }
        }
    }
}