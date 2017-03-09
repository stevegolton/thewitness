CC=gcc
CFLAGS=
LIBS=
OBJ=main.o puzzle.o sbuf.o grid_puzzle_factory.o puzzle_solver.o puzzle_printer.o
BIN=runme

%.o: %.c
	$(CC) -c -o $@ $<

$(BIN): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o $(BIN)