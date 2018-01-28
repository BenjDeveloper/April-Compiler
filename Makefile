april: main.o parser.o lexer.o
	g++ -o april $^ --std=gnu++11

main.o: lexer.cpp parser.cpp main.cpp
	g++ -c main.cpp --std=gnu++11

lexer.cpp: lexer.l parser.h
	flex -o lexer.cpp lexer.l

parser.cpp parser.h: parser.y
	bison -o parser.cpp parser.y

.PHONY:clean
clean:
	rm *.o april lexer.cpp parser.h parser.cpp