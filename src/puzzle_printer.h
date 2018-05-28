#ifndef PUZZLE_PRINTER_H
#define PUZZLE_PRINTER_H

#include <memory>

#include "puzzle.h"

class PuzzlePrinter
{
public:
	PuzzlePrinter(std::shared_ptr<Puzzle> puzzle_to_print);
	~PuzzlePrinter();
	void print_puzzle();
private:
	std::shared_ptr<Puzzle> puzzle;
	char *sbuf;
	int x_max;
	int y_max;
};

#endif
