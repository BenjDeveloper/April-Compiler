all:april

CC = g++

OBJS = parser.o				\
	lexer.o					\
	integer.o				\
	double.o				\
	binaryope.o				\
	block.o					\
	exprstatement.o			\
	codegencontext.o 		\
	identifier.o	 		\
	vardeclaration.o	 	\
	methodcall.o		 	\
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
	win_bison -o $@ $<

lexer.cpp: lexer.l parser.h
	win_flex -o $@ $^ 

.PHONY: clean
clean:
	cls && del $(OBJS) parser.cpp lexer.cpp parser.h

.PHONY: clean_all
clean_all:
	cls && del $(OBJS) parser.cpp lexer.cpp parser.h *.exe