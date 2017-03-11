#ifndef GRIDFILE_PUZZLE_FACTORY_H
#define GRIDFILE_PUZZLE_FACTORY_H

#include <memory>		// shared_ptr
#include <string>		// std::string
#include "puzzle.h"		// Puzzle

class GridFilePuzzleFactory
{
public:
	GridFilePuzzleFactory(std::string filename);
	std::shared_ptr<Puzzle> make_puzzle();
private:
	std::string filename;
};

#endif
