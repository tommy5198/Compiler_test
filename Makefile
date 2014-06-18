CC = gcc
CPPC = g++
DEP = Lexer.h Parser.h ParseTable.h ParseTree.h SymbolTable.h Quadruple.h
CDEP = Lexer.h ParseTree.h
OBJ = Lexer.o Parser.o ParseTable.o ParseTree.o	SymbolTable.o Quadruple.o
TARGET = g--

%.o: %.c $(CDEP)
	$(CC) -c -o $@ $<

%.o: %.cpp $(DEP)
	$(CPPC) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CPPC) -o $@ $^ $(FLAG)

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJ) *~
