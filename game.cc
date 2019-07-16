#include "game.h"
#include "keyboardController.h"
#include "textView.h"
#include "exception.h"
#include "chessBoard.h"
#include "color.h"
#include "card.h"

#include <memory>

using namespace std;

// Constructor

Game::Game(bool textOnly) : chessBoard{make_unique<ChessBoard>()}, curPlayer{Color::WHITE}, lastCardApplied{Card::NONE}, winner{Color::NONE}, tie{false}, validMoves{false}  {
    addController(move(make_unique<KeyboardController>()));
    // TODO MICHELLE: Update the numbers to variables
    addView(move(make_unique<TextView>(*this, 8, 8)));
}

// Accessors

ChessBoard* Game::getChessBoard() {
    return chessBoard.get();
}

Card Game::getLastCardApplied() {
    return lastCardApplied;
}

Color Game::getWinner() {
    return winner;
}

bool Game::isTie() {
    return tie;
}

bool Game::showingValidMoves() {
    return validMoves;
}

// Public Methods

void Game::start() {
    displayViews(); // Initial display

    Command cmd;
    bool enhancementsOn = false;

    while (cin) {
        cmd = getCommand();

        // TODO MICHELLE: Decide what to do about reading from cin
        // TODO MICHELLE: Modify all exceptions to update views
        if (cmd == Command::QUIT) {
            break;
        } else if (cmd == Command::NONE) {
            continue;
        } else if (cmd == Command::INVALID) { // TODO MICHELLE: modify this to update views
            cerr << "Invalid command." << endl;
            continue;
        } else if (cmd == Command::MOVE) {
            Point curPos;
            Point newPos;
            cin >> curPos >> newPos;
            int end;

            try {
                end = playTurn(curPos, newPos);
                if (end) break; // TODO MICHELLE: Is there a more elegant way of doing this?
            } catch (InvalidMoveException& e) {
                cerr << e.what() << endl;
            }
        } else if (cmd == Command::RESTART) {
            // TODO MICHELLE: RESTART GAME
        } else if (cmd == Command::DEFAULTPROMOTION) {
            char piece;
            cin >> piece;
            
            try {
                setDefaultPromotionPiece(piece);
            } catch (InvalidDefaultPromotionPieceException& e) {
                cerr << e.what() << endl;
            }
        } else if (enhancementsOn && cmd == Command::VALIDMOVES) {
            Point pos;
            cin >> pos;
            try {
                showValidMoves(pos);
            } catch (InvalidMoveException& e) {
                cerr << e.what() << endl;
            }
        } else if (cmd == Command::ENHANCEMENTSON) {
            enhancementsOn = true;
        } else if (cmd == Command::ENHANCEMENTSOFF) {
            enhancementsOn = false;
        }
    }
}

void Game::setDefaultPromotionPiece(char piece) {
    chessBoard->setDefaultPromotionPiece(curPlayer, piece);
}

bool Game::playTurn(Point& curPos, Point& newPos) {
    chessBoard->makeMove(curPos, newPos, curPlayer);
    lastCardApplied = chessBoard->getCardAt(newPos);
    switch (lastCardApplied.getValue()) {
        case Card::CURSE:
            chessBoard->updateHP(curPlayer == Color::WHITE ? Color::BLACK : Color::WHITE, -1);
            break;
        case Card::PLUSONEHP:
            chessBoard->updateHP(curPlayer, 1);
            break;
        case Card::FIRECOLUMN:
        case Card::MOAT:
        case Card::DESTRUCTION:
        case Card::RESURRECTION:
            chessBoard->applyCardAt(curPlayer, newPos);
            break;
        default:
            break;
    }
    chessBoard->setCardAt(newPos, Card::NONE);

    // Check for winner
    bool gameEnded = checkWin();

    // Switch turn if ENCHANTMENT card not applied
    if (!(lastCardApplied == Card::ENCHANTMENT)) curPlayer = curPlayer == Color::WHITE ? Color::BLACK : Color::WHITE;

    // Notify observers to display screen
    displayViews();

    return gameEnded;
}

void Game::showValidMoves(Point& pos) {
    chessBoard->markValidMoves(pos, curPlayer, true);
    validMoves = true;
    displayViews();
    chessBoard->markValidMoves(pos, curPlayer, false);
    validMoves = false;
} 

bool Game::checkWin() {
    Color opponent = curPlayer == Color::WHITE ? Color::BLACK : Color::WHITE;

    if(chessBoard->getPlayerHp(opponent) <= 0 || !chessBoard->armyIsAlive(opponent)){
        winner = curPlayer;
        return true;
    }

    if(chessBoard->checkStandstill()) {
        if (chessBoard->getPlayerHp(opponent) > chessBoard->getPlayerHp(curPlayer)) {
            winner = opponent;
        } else if (chessBoard->getPlayerHp(opponent) == chessBoard->getPlayerHp(curPlayer)) {
            tie = true;
        } else {
            winner = curPlayer;
        }
        return true;
    }
    
    return false;
}