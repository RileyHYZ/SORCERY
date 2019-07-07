CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = main
OBJECTS = main.o chessBoard.o chessPiece.o game.o observer.o point.o square.o subject.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

