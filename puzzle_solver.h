#ifndef PUZZLE_SOLVER_H
#define PUZZLE_SOLVER_H

#include <memory>

#include "puzzle.h"
#include "node.h"

class PuzzleSolver
{
public:
	PuzzleSolver(std::shared_ptr<Puzzle> puzzle);
	bool find_one_solution();
private:
	bool validate_route();
	int follow_route(Node *node);
	bool find_squares(Node *node, enum nodecolour col);
	std::shared_ptr<Puzzle> puzzle;
};

#endif
