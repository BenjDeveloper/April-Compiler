CC = clang++

all: april

OBJS =	parser.o				\
		lexer.o					\
		integer.o				\
		boolean.o				\
		double.o				\
		codegencontext.o		\
		block.o					\
		conditional.o			\
		identifier.o			\
		string.o				\
		assignment.o			\
		vardeclaration.o		\
		methodcall.o			\
		exprstatement.o			\
		bioperator.o			\
		unaryope.o				\
		nativefn.o				\
		vardeclarationdeduce.o	\
		comparasionope.o		\
		scope.o					\
		forloop.o				\
		function.o				\
		return.o				\
		assigbiope.o			\
		main.o					\

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++11
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lm -lz -lncurses -rdynamic
LIBS = `$(LLVMCONFIG) --libs`

.PHONY: clean
clean:
	clear && rm -f $(OBJS) parser.cpp parser.h lexer.cpp

%.o: src/%.cpp
	$(CC) -c $(CPPFLAGS) $<

parser.cpp: src/parser.y
	bison -o $@ $<

lexer.cpp: src/lexer.l parser.h
	flex -o $@ $<

april: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)
