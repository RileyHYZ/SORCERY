#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__
#include "point.h"
#include "color.h"

class ChessPiece {
		Color color;
		virtual bool isValidMove(Point&, Point&) = 0;

	public:
		ChessPiece(Color); 
		virtual ~ChessPiece();
		bool checkValidMove(Point&, Point&);
};

class Pawn : public ChessPiece {
	public:
		Pawn(Color);
		bool isValidMove(Point&, Point&) override;
};

class Knight : public ChessPiece {
	public:
		Knight(Color);
		bool isValidMove(Point&, Point&) override;
};

class Bishop : public ChessPiece {
	public:
		Bishop(Color);
		bool isValidMove(Point&, Point&) override;
};

class Rook : public ChessPiece {
	public:
		Rook(Color);
		bool isValidMove(Point&, Point&) override;
};

class King : public ChessPiece {
	public:
		King(Color);
		bool isValidMove(Point&, Point&) override;
};

class Queen : public ChessPiece {
	public:
		Queen(Color);
		bool isValidMove(Point&, Point&) override;
};

#endif