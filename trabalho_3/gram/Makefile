all: simbs codigo
	echo "=== Execução ==="
	../mdp/interpretador < codigo
	
codigo: simbs entrada.txt
	./simbs < entrada.txt > codigo
	echo "=== Codigo ==="
	cat codigo

simbs: lex.yy.c y.tab.c
	g++ y.tab.c -o simbs -lfl -Wall
	
lex.yy.c: simbs.l
	lex simbs.l
	
y.tab.c: simbs.y
	yacc simbs.y
	
clean: 
	rm -f lex.yy.c y.tab.c simbs


