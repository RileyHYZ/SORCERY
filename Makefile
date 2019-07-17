CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = main
OBJECTS = main.o card.o chessBoard.o chessPiece.o controller.o model.o keyboardController.o game.o exception.o point.o square.o  window.o textView.o graphicalView.o windowController.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L/opt/X11/lib -lX11 -lpng

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

