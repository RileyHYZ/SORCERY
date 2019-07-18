#include "graphicalView.h"
#include "game.h"
#include "square.h"

#include <iostream>
#include <unordered_map>

using namespace std;

// Constructor

GraphicalView::GraphicalView(Game& model, int numCols) : numCols{numCols}, model{model} {
    window = move(make_unique<Xwindow>());
}

// Private Methods

void GraphicalView::drawHP(ChessBoard* chessBoard) {
    for(int i = 0; i < chessBoard->getPlayerHP(Color::WHITE); i++) {
        window->fillRectangle(740 - 30 * i, 460, 20, 20, 2);
    }
    for(int i = 0; i < chessBoard->getPlayerHP(Color::BLACK); i++) {
        window->fillRectangle(360 + 30 * i, 30, 20, 20, 2);
    }
}

void GraphicalView::drawChessBoard(ChessBoard *chessBoard) {
    window->drawRectangle(390, 90, 320, 320);
    int row = 0, col = 0;
    for(Square& square: *chessBoard) {
        if (square.getColor() == Color::BLACK) {
            window->fillRectangle(390 + 40 * col, 90 + 40 * row, 40, 40);
        }
        col ++;
        if (col == numCols) {
            col = 0;
            row ++;
        }
    }
}

void GraphicalView::drawChessPieces(ChessBoard *chessBoard) {
    int row = 0, col = 0;
    for (Square& square : *chessBoard) {
        if (square.getPiece() != nullptr) {
            string path;
            string name = square.getPiece()->getName();
            if (square.getPiece()->getColor() == Color::BLACK) name = "b" + name;
            if (square.getColor() == Color::WHITE) path = "./pieces/" + name + ".png";
            else path = "./pieces/" + name + "2.png";
            window->putImage(395 + 40 * col, 95 + 40 * row, path.c_str());
        }
        if (square.isValid()){
            window->fillRectangle(404 + 40 * col, 104 + 40 * row, 10, 10, 2);
        }
        col ++;
        if (col == numCols) {
            col = 0;
            row ++;
        }
    }
}

void GraphicalView::updateAbilityCard(Card card) {
    if (card != Card::NONE) {
        string path = "./cards/" + card.getName()+".png";
        window->putImage(70, 140, path.c_str());
    }
}

void GraphicalView::drawCommandButtons() {
    window->drawString(60, 30, "SELECT A COMMAND");
    
    window->drawRectangle(55, 40, 40, 23);
    window->drawString(65, 56, "MOVE");
    window->drawRectangle(100, 40, 50, 23);
    window->drawString(104, 56, "RESTART");
    window->drawRectangle(155, 40, 40, 23);
    window->drawString(165, 56, "QUIT");
    
    window->drawRectangle(55, 73, 80, 23);
    window->drawString(70, 90, "PROMOTION");
    window->putImage(140,70,"./pieces/queen.png");
    window->putImage(180,70,"./pieces/rook.png");
    window->putImage(220,70,"./pieces/bishop.png");
    window->putImage(260,70,"./pieces/knight.png");

    window->drawRectangle(55, 106, 120, 23);
    window->drawString(75, 123, "ENHANCEMENTS");
    window->drawRectangle(200, 106, 80, 23);
    window->drawString(210, 123, "VALID MOVE");

}

// Public Methods

void GraphicalView::displayView() {
    ChessBoard* board = model.getChessBoard();
    window->clearWindow();

    drawChessBoard(board);
    drawHP(board);
    drawChessPieces(board);
    updateAbilityCard(model.getCardApplied());
    drawCommandButtons();
}

void GraphicalView::displayMessage(const string& msg) {
    window->clearArea(38, 418, 430, 22);
    if (msg.size() > 0)
        window->drawString(40, 430, msg);
}

Xwindow& GraphicalView::getWindow() {
    return *(window.get());
}

