all: saida entrada.txt
	./saida < entrada.txt

lex.yy.c: 2ndlex.l
	lex 2ndlex.l

saida: lex.yy.c main.cc
	g++ lex.yy.c main.cc -o saida -lfl

clean:
	rm saida lex.yy.c