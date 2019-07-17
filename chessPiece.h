#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__

#include <vector>

#include "point.h"
#include "color.h"

class ChessPiece {
		Color color;
	
	protected:
		std::string type;
		
		virtual std::string displayIcon() = 0;
		virtual std::vector<Point> piecePath(Point&, Point&) = 0;
		virtual bool isValidMove(Point&, Point&, bool) = 0;
		virtual std::vector<Point> validMoves(Point&, Color, int, int) = 0;

		std::vector<Point> getHorizontalPath(Point&, Point&);
		std::vector<Point> getVerticalPath(Point&, Point&);
		std::vector<Point> getDiagonalPath(Point&, Point&);
		std::vector<Point> getHorizontalMoves(Point&, int ,int);
		std::vector<Point> getVerticalMoves(Point&, int, int);
		std::vector<Point> getDiagonalMoves(Point&, int, int);
		
	public:
		ChessPiece(Color);
		virtual ~ChessPiece();

		Color getColor();
		std::string getViewIcon();
		std::string getType();
		
		std::vector<Point> getPiecePath(Point&, Point&);
		bool checkValidMove(Point&, Point&, bool);
		std::vector<Point> getValidMoves(Point&, Color, int, int);
};

class Pawn : public ChessPiece {
	public:
		Pawn(Color);
		std::string displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&) override;
		bool isValidMove(Point&, Point&, bool) override;
		std::vector<Point> validMoves(Point&, Color, int, int);
};

class Knight : public ChessPiece {
	public:
		Knight(Color);
		std::string displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&) override;
		bool isValidMove(Point&, Point&, bool) override;
		std::vector<Point> validMoves(Point&, Color, int, int);
};

class Bishop : public ChessPiece {
	public:
		Bishop(Color);
		std::string displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&) override;
		bool isValidMove(Point&, Point&, bool) override;
		std::vector<Point> validMoves(Point&, Color, int, int);
};

class Rook : public ChessPiece {
	public:
		Rook(Color);
		std::string displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&) override;
		bool isValidMove(Point&, Point&, bool) override;
		std::vector<Point> validMoves(Point&, Color, int, int);
};

class King : public ChessPiece {
	public:
		King(Color);
		std::string displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&) override;
		bool isValidMove(Point&, Point&, bool) override;
		std::vector<Point> validMoves(Point&, Color, int, int);
};

class Queen : public ChessPiece {
	public:
		Queen(Color);
		std::string displayIcon() override;
		std::vector<Point> piecePath(Point&, Point&) override;
		bool isValidMove(Point&, Point&, bool) override;
		std::vector<Point> validMoves(Point&, Color, int, int);
};

#endif
