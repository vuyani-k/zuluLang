CC=gcc
CFLAGS=-I.
DEPS=compiler.h tokens.h lexer.h parser.h gen.h
OBJ=compiler.o lexer.o parser.o gen.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

compiler: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) 

run: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS); ./compiler

clean: 
	rm -f *.o
