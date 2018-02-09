CC = g++

all: april

OBJS =	parser.o	\
		buildfn.o	\
		codegen.o	\
		main.o		\
		lexer.o		\

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++11
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lm -lz -lncurses -rdynamic
LIBS = `$(LLVMCONFIG) --libs`

.PHONY: clean
clean:
	clear && rm -f $(OBJS) parser.cpp parser.h lexer.cpp

parser.cpp: parser.y
	bison -o $@ $<

parser.h: parser.cpp

lexer.cpp: lexer.l parser.h
	flex -o $@ $<

%.o: %.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $<

april: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)