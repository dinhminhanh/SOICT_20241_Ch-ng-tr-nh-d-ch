CPP      = g++
CC       = gcc
WINDRES  = 
OBJ      = main.o charcode.o codegen.o debug.o error.o instructions.o parser.o reader.o scanner.o semantics.o symtab.o token.o
LINKOBJ  = $(OBJ)
LIBS     =
INCS     = -I/usr/local/include
CXXINCS  = -I/usr/local/include
BIN      = CodeGen_d3_complete
CXXFLAGS = $(CXXINCS)
CFLAGS   = $(INCS)
RM       = rm -f




.PHONY: all all-before all-after clean clean-custom




all: all-before $(BIN) all-after




clean: clean-custom
	$(RM) $(OBJ) $(BIN)




$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)




main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)




charcode.o: charcode.c
	$(CC) -c charcode.c -o charcode.o $(CFLAGS)




codegen.o: codegen.c
	$(CC) -c codegen.c -o codegen.o $(CFLAGS)




debug.o: debug.c
	$(CC) -c debug.c -o debug.o $(CFLAGS)




error.o: error.c
	$(CC) -c error.c -o error.o $(CFLAGS)




instructions.o: instructions.c
	$(CC) -c instructions.c -o instructions.o $(CFLAGS)




parser.o: parser.c
	$(CC) -c parser.c -o parser.o $(CFLAGS)




reader.o: reader.c
	$(CC) -c reader.c -o reader.o $(CFLAGS)




scanner.o: scanner.c
	$(CC) -c scanner.c -o scanner.o $(CFLAGS)




semantics.o: semantics.c
	$(CC) -c semantics.c -o semantics.o $(CFLAGS)




symtab.o: symtab.c
	$(CC) -c symtab.c -o symtab.o $(CFLAGS)




token.o: token.c
	$(CC) -c token.c -o token.o $(CFLAGS)



