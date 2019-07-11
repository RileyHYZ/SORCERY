#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__
#include "point.h"
#include "color.h"

class ChessPiece {
		Color color;

		virtual char displayIcon() = 0;
		virtual bool isValidMove(Point&, Point&, bool) = 0;
		
	public:
		ChessPiece(Color); 
		Color getColor();
		virtual ~ChessPiece();

		Color getColor();
		char getDisplayIcon();

		bool checkValidMove(Point&, Point&, bool);
};

class Pawn : public ChessPiece {
	public:
		Pawn(Color);
		char displayIcon() override;
		bool isValidMove(Point&, Point&, bool) override;
};

class Knight : public ChessPiece {
	public:
		Knight(Color);
		char displayIcon() override;
		bool isValidMove(Point&, Point&, bool) override;
};

class Bishop : public ChessPiece {
	public:
		Bishop(Color);
		char displayIcon() override;
		bool isValidMove(Point&, Point&, bool) override;
};

class Rook : public ChessPiece {
	public:
		Rook(Color);
		char displayIcon() override;
		bool isValidMove(Point&, Point&, bool) override;
};

class King : public ChessPiece {
		int hp;
	public:
		King(Color);
		char displayIcon() override;
		int getHP();
		void setHP(int);
		bool isValidMove(Point&, Point&, bool) override;
};

class Queen : public ChessPiece {
	public:
		Queen(Color);
		char displayIcon() override;
		bool isValidMove(Point&, Point&, bool) override;
};

#endif