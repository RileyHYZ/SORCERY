#ifndef __GRAPHICALVIEW_H__
#define __GRAPHICALVIEW_H__

#include "view.h"
#include "chessBoard.h"
#include "window.h"

#include <iostream>
#include <vector>

class Game;

class GraphicalView : public View {
	int numCols;
    Game& model;
	std::unique_ptr<Xwindow> window;

	void drawHP(ChessBoard*);
	void drawChessBoard(ChessBoard*);
	void drawChessPieces(ChessBoard*);
	void updateAbilityCard(Card);
	void drawCommandButtons();

  public:
	GraphicalView(Game&, int);

	void displayView() override;
	void displayMessage(const std::string& msg) override;
	Xwindow& getWindow();
};

#endif