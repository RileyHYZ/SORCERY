#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__

#include "color.h"

#include <string>
#include <vector>

class Point;

class ChessPiece {
	Color color;
	std::string name;

	virtual char displayIcon() = 0;
	virtual bool isValidMove(Point&, Point&, bool) = 0;
	virtual std::vector<Point> farthestValidMoves(Point&, Color, int, int) = 0;
	virtual std::vector<Point> path(Point&, Point&) = 0;

  protected:
	bool isHorizontalMove(Point&, Point&);
	bool isVerticalMove(Point&, Point&);
	bool isDiagonalMove(Point&, Point&, int = 0);
	std::vector<Point> getHorizontalPath(Point&, Point&);
	std::vector<Point> getVerticalPath(Point&, Point&);
	std::vector<Point> getDiagonalPath(Point&, Point&);
	std::vector<Point> farthestHorizontalMoves(Point&, int);
	std::vector<Point> farthestVerticalMoves(Point&, int);
	std::vector<Point> farthestDiagonalMoves(Point&, int, int);
		
  public:
	ChessPiece(Color, std::string);
	virtual ~ChessPiece() = default;

	Color getColor();
	std::string getName();
	char getDisplayIcon();
	
	bool checkValidMove(Point&, Point&, bool);
	std::vector<Point> getValidMoves(Point&, Color, int, int);
	std::vector<Point> getPath(Point&, Point&);
};

class Pawn : public ChessPiece {
  public:
	Pawn(Color);
	char displayIcon() override;
	bool isValidMove(Point&, Point&, bool) override;
	std::vector<Point> farthestValidMoves(Point&, Color, int, int) override;
	std::vector<Point> path(Point&, Point&) override;
};

class Knight : public ChessPiece {
  public:
	Knight(Color);
	char displayIcon() override;
	bool isValidMove(Point&, Point&, bool) override;
	std::vector<Point> farthestValidMoves(Point&, Color, int, int) override;
	std::vector<Point> path(Point&, Point&) override;
};

class Bishop : public ChessPiece {
  public:
	Bishop(Color);
	char displayIcon() override;
	bool isValidMove(Point&, Point&, bool) override;
	std::vector<Point> farthestValidMoves(Point&, Color, int, int) override;
	std::vector<Point> path(Point&, Point&) override;
};

class Rook : public ChessPiece {
  public:
	Rook(Color);
	char displayIcon() override;
	bool isValidMove(Point&, Point&, bool) override;
	std::vector<Point> farthestValidMoves(Point&, Color, int, int) override;
	std::vector<Point> path(Point&, Point&) override;
};

class King : public ChessPiece {
  public:
	King(Color);
	char displayIcon() override;
	bool isValidMove(Point&, Point&, bool) override;
	std::vector<Point> farthestValidMoves(Point&, Color, int, int) override;
	std::vector<Point> path(Point&, Point&) override;
};

class Queen : public ChessPiece {
  public:
	Queen(Color);
	char displayIcon() override;
	bool isValidMove(Point&, Point&, bool) override;
	std::vector<Point> farthestValidMoves(Point&, Color, int, int) override;
	std::vector<Point> path(Point&, Point&) override;
};

#endif
