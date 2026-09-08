CC = gcc
CXX = g++
CFLAGS = -Wall
CXXFLAGS = -Wall -std=c++17

all: lexer calc

lexer: lexer.l
	flex -o lex.yy.c lexer.l
	$(CC) $(CFLAGS) lex.yy.c -o lexer -lfl

calc: scanner.ll processor.cpp scanner.hpp tokens.hpp
	flex -o scanner.yy.cpp scanner.ll
	$(CXX) $(CXXFLAGS) scanner.yy.cpp processor.cpp -o calc

clean:
	rm -f lex.yy.c lexer scanner.yy.cpp calc
