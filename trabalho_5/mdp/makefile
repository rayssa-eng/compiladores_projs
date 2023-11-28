
all: lex.yy.mdp.o var_object.cc mdp.h mdp.cc
	g++ lex.yy.mdp.o mdp.cc -lfl -o interpretador 
		
lex.yy.mdp.o: lex.yy.mdp.c 
	g++ -c -lfl lex.yy.mdp.c 
	
lex.yy.mdp.c: mdp.l 
	lex -o lex.yy.mdp.c mdp.l 
	