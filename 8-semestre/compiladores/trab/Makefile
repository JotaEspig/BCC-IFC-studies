CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -std=gnu11 -Isrc -Ibuild
LDLIBS  = -lm

OBJS = build/parser.tab.o build/lex.yy.o build/ast.o build/dados.o \
       build/semantico.o build/gerador.o build/main.o

all: dashc

dashc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

build:
	mkdir -p build

# bison gera o parser (e o cabeçalho com os tokens, usado pelo lexer)
build/parser.tab.c build/parser.tab.h: src/parser.y | build
	bison -d -o build/parser.tab.c src/parser.y

# flex gera o analisador léxico
build/lex.yy.c: src/lexer.l build/parser.tab.h | build
	flex -o build/lex.yy.c src/lexer.l

build/parser.tab.o: build/parser.tab.c src/ast.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/lex.yy.o: build/lex.yy.c src/ast.h
	$(CC) $(CFLAGS) -Wno-unused-function -c -o $@ $<

build/%.o: src/%.c src/ast.h src/dados.h src/semantico.h src/gerador.h | build
	$(CC) $(CFLAGS) -c -o $@ $<

# compila os exemplos (sem abrir uma aba do navegador para cada um)
exemplos: dashc
	./dashc exemplos/vendas.dash --nao-abrir
	./dashc exemplos/clima.dash --nao-abrir

clean:
	rm -rf build dashc exemplos/*.html

.PHONY: all exemplos clean
