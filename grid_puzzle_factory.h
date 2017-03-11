#ifndef GRID_PUZZLE_FACTORY_H
#define GRID_PUZZLE_FACTORY_H

#include <memory>		// shared_ptr
#include "puzzle.h"		// Puzzle

class GridPuzzleFactory
{
public:
	GridPuzzleFactory(int cols, int rows);
	std::shared_ptr<Puzzle> make_puzzle();
private:
	int cols;
	int rows;
};

#endif /* GRID_PUZZLE_FACTORY_H_ */
