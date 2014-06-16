CC = gcc
CPPC = g++
DEP = Lexer.h Parser.h ParseTable.h ParseTree.h SymbolTable.h
OBJ = Lexer.o Parser.o ParseTable.o ParseTree.o	SymbolTable.o
TARGET = g--

%.o: %.c $(DEP)
	$(CC) -c -o $@ $<

%.o: %.cpp $(DEP)
	$(CPPC) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CPPC) -o $@ $^ $(FLAG)

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJ) *~
