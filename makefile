CC = g++

all: april

OBJS =	parser.o				\
		lexer.o					\
		integer.o				\
		boolean.o				\
		double.o				\
		codegencontext.o		\
		block.o					\
		identifier.o			\
		string.o				\
		assignment.o			\
		vardeclaration.o		\
		methodcall.o			\
		exprstatement.o			\
		bioperator.o			\
		nativefn.o				\
		vardeclarationdeduce.o	\
		main.o					\

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++11
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lm -lz -lncurses -rdynamic
LIBS = `$(LLVMCONFIG) --libs`

.PHONY: clean
clean:
	clear && rm -f $(OBJS) parser.cpp parser.h lexer.cpp

integer.o: src/integer.cpp
	$(CC) -c $(CPPFLAGS) $<

double.o: src/double.cpp
	$(CC) -c $(CPPFLAGS) $<

codegencontext.o: src/codegencontext.cpp
	$(CC) -c $(CPPFLAGS) $<

block.o: src/block.cpp
	$(CC) -c $(CPPFLAGS) $<

identifier.o: src/identifier.cpp
	$(CC) -c $(CPPFLAGS) $<

string.o: src/string.cpp
	$(CC) -c $(CPPFLAGS) $<

assignment.o: src/assignment.cpp
	$(CC) -c $(CPPFLAGS) $<

vardeclaration.o: src/vardeclaration.cpp
	$(CC) -c $(CPPFLAGS) $<

methodcall.o: src/methodcall.cpp
	$(CC) -c $(CPPFLAGS) $<

exprstatement.o: src/exprstatement.cpp
	$(CC) -c $(CPPFLAGS) $<

parser.o: parser.cpp parser.h
	$(CC) -c $(CPPFLAGS) $<

parser.cpp: src/parser.y
	bison -o $@ $<

bioperator.o: src/bioperator.cpp
	$(CC) -c $(CPPFLAGS) $<

lexer.cpp: src/lexer.l parser.h
	flex -o $@ $<

lexer.o: lexer.cpp parser.h
	$(CC) -c $(CPPFLAGS) -o $@ $<

nativefn.o: src/nativefn.cpp
	$(CC) -c $< --std=c++11

vardeclarationdeduce.o: src/vardeclarationdeduce.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $<

boolean.o: src/boolean.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $<

main.o: main.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $<

april: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)