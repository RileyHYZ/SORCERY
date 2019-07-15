#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__

#include <vector>

#include "point.h"
#include "color.h"

class ChessPiece {
		Color color;
		std::string type;

		virtual char displayIcon() = 0;
		virtual std::vector<Point> piecePath(Point&, Point&) = 0;
		virtual bool isValidMove(Point&, Point&, bool) = 0;

	protected:
		std::vector<Point> getHorizontalPath(Point&, Point&);
		std::vector<Point> getVerticalPath(Point&, Point&);
		std::vector<Point> getDiagonalPath(Point&, Point&);
		
	public:
		ChessPiece(Color);
		virtual ~ChessPiece();

		void setType(std::string);

		std::string getType();
		Color getColor();
		char getDisplayIcon();
		

		std::vector<Point> getPiecePath(Point&, Point&);
		bool checkValidMove(Point&, Point&, bool);
};

class Pawn : public ChessPiece {
	public:
		Pawn(Color);
		char displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&);
		bool isValidMove(Point&, Point&, bool) override;
};

class Knight : public ChessPiece {
	public:
		Knight(Color);
		char displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&);
		bool isValidMove(Point&, Point&, bool) override;
};

class Bishop : public ChessPiece {
	public:
		Bishop(Color);
		char displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&);
		bool isValidMove(Point&, Point&, bool) override;
};

class Rook : public ChessPiece {
	public:
		Rook(Color);
		char displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&);
		bool isValidMove(Point&, Point&, bool) override;
};

class King : public ChessPiece {
	public:
		King(Color);
		char displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&);
		bool isValidMove(Point&, Point&, bool) override;
};

class Queen : public ChessPiece {
	public:
		Queen(Color);
		char displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&);
		bool isValidMove(Point&, Point&, bool) override;
};

#endif
