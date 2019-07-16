#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__
#include "point.h"
#include "color.h"

class ChessPiece {
		Color color;
		std::string type;

		virtual std::string displayIcon() = 0;
		virtual bool isValidMove(Point&, Point&, bool) = 0;
	
	protected:
		void setType(std::string);
		
	public:
		ChessPiece(Color); 
		virtual ~ChessPiece();

		Color getColor();
		std::string getDisplayIcon();
		std::string getType();

		bool checkValidMove(Point&, Point&, bool);
};

class Pawn : public ChessPiece {
	public:
		Pawn(Color);
		std::string displayIcon() override;
		bool isValidMove(Point&, Point&, bool) override;
};

class Knight : public ChessPiece {
	public:
		Knight(Color);
		std::string displayIcon() override;
		bool isValidMove(Point&, Point&, bool) override;
};

class Bishop : public ChessPiece {
	public:
		Bishop(Color);
		std::string displayIcon() override;
		bool isValidMove(Point&, Point&, bool) override;
};

class Rook : public ChessPiece {
	public:
		Rook(Color);
		std::string displayIcon() override;
		bool isValidMove(Point&, Point&, bool) override;
};

class King : public ChessPiece {
	public:
		King(Color);
		std::string displayIcon() override;
		bool isValidMove(Point&, Point&, bool) override;
};

class Queen : public ChessPiece {
	public:
		Queen(Color);
		std::string displayIcon() override;
		bool isValidMove(Point&, Point&, bool) override;
};

#endif
