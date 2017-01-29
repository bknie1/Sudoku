# Variable CC = compiler of choice.
CC=c++
# CFLAGS = compiler options.
CFLAGS=-c -Wall -std=c++11

all: sudoku

Sudoku: Sudoku.o Game.o Board.o Square.o Cluster.o BoardState.o Exceptions.o Viewer.o Canvas.o MixedChar.o GridChar.o Tools.o
	$(CC) Sudoku.o Game.o Board.o Square.o Cluster.o BoardState.o Exceptions.o Viewer.o Canvas.o MixedChar.o GridChar.o Tools.o -o Sudoku

Sudoku.o: Sudoku.cpp
	$(CC) -c Sudoku.cpp

Game.o: Game.cpp
	$(CC) -c Game.cpp

Board.o: Board.cpp
	$(CC) -c Board.cpp

Square.o: Square.cpp
	$(CC) -c Square.cpp

Cluster.o: Cluster.cpp
	$(CC) -c Cluster.cpp

BoardState.o: BoardState.cpp
	$(CC) -c BoardState.cpp

Exceptions.o: Exceptions.cpp
	$(CC) -c Exceptions.cpp

Viewer.o: Viewer.cpp
	$(CC) -c Viewer.cpp

Canvas.o: Canvas.cpp
	$(CC) -c Canvas.cpp

MixedChar.o: MixedChar.cpp
	$(CC) -c MixedChar.cpp

GridChar.o: GridChar.cpp
	$(CC) -c GridChar.cpp

Tools.o: Tools.cpp
	$(CC) -c Tools.cpp

clean:
	rm *o sudoku