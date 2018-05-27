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
	methodstruct.o		 	\
	booleancmp.o		 	\
	if.o				 	\
	boolean.o				\
	for.o					\
	assignment.o			\
	assigbioperator.o		\
	not.o					\
	function.o				\
	vardeclarationdeduce.o	\
	stringarray.o			\
	return.o				\
	break.o					\
	list.o					\
	listaccess.o			\
	assignmentlist.o		\
	funclist.o				\
	methodhandlelist.o		\
	methodhandlestring.o	\
	methodhandlecast.o		\
	methodhandlefile.o		\
	methodhandleio.o		\
	vardeclarationglobal.o	\
	foriteration.o			\
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
	cls && del $(OBJS) parser.cpp lexer.cpp

.PHONY: clean_all
clean_all:
	cls && del $(OBJS) parser.cpp lexer.cpp *.exe