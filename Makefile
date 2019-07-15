CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = main
OBJECTS = main.o chessBoard.o chessPiece.o output.o game.o observer.o point.o square.o subject.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L/opt/X11/lib -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

