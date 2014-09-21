all:
	bison -d -Wall grammar.yy
	flex flex.l
	g++ -c lex.yy.c -o lexer.o  -L"C:/Program Files (x86)/GnuWin32/lib" -lfl  -O3 #-Wall
	g++ -c func.cpp -o func.o   -L"C:/Program Files (x86)/GnuWin32/lib" -lfl  -O3 #-Wall
	g++ -c Parser.cpp -o parser.o -L . -lfunc -llexer -L"C:/Program Files (x86)/GnuWin32/lib" -lfl  -O3 #-Wall 
	g++ -c ast.cpp -o ast.o  -O3 #-Wall 
	ar rcs libparser.a parser.o ast.o lexer.o func.o 
	g++ main.cpp -L .  -lparser -L "C:/Program Files (x86)/GnuWin32/lib" -lfl  -o inter.exe  -Wall -O3
