#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__
#include "Point.h"

class ChessPiece {
    Color color;
		virtual bool isValidMove(Point curPos, Point newPos);//chesspiece cannot be a pure virtual

	public:
		ChessPiece(Color); 
		bool checkValidMove(Point curPos, Point newPos);
};

class Pawn {
	public:
		bool isValidMove(Point curPos, Point newPos);
};
class Knight {
	public:
		bool isValidMove(Point curPos, Point newPos);
};
class Bishop {
	public:
		bool isValidMove(Point curPos, Point newPos);
};
class Rook {
	public:
		bool isValidMove(Point curPos, Point newPos);
};
class King {
	public:
		bool isValidMove(Point curPos, Point newPos);
};
class Queen {
	public:
		bool isValidMove(Point curPos, Point newPos);
};

#endif