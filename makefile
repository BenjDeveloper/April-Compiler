all:april

CC = g++

OBJS = parser.o				\
	lexer.o					\
	symbol.o				\
	integer.o				\
	double.o				\
	string.o				\
	binaryope.o				\
	block.o					\
	exprstatement.o			\
	codegencontext.o 		\
	identifier.o	 		\
	vardeclaration.o	 	\
	methodcall.o		 	\
	booleancmp.o		 	\
	assignment.o			\
	main.o					\

CPPFLAGS = -std=gnu++11

april: $(OBJS)
	$(CC) $(OBJS) -o $@ $(CPPFLAGS)
	make clean

%.o: %.cpp
	$(CC) -c $< $(CPPFLAGS)

%.o: src/%.cpp
	$(CC) -c $< $(CPPFLAGS)

parser.cpp: parser.y
	bison -o $@ $<

lexer.cpp: lexer.l parser.h
	flex -o $@ $^ 

.PHONY: clean
clean:
	clear && rm $(OBJS) parser.cpp lexer.cpp

.PHONY: clean_all
clean_all:
	clear && rm $(OBJS) parser.cpp lexer.cpp 