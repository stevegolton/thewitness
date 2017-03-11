#ifndef PUZZLE_SOLVER_H
#define PUZZLE_SOLVER_H

#include <memory>

#include "sbuf.h"
#include "puzzle.h"

class PuzzleSolver
{
public:
	PuzzleSolver(std::shared_ptr<Puzzle> puzzle);
	void find_one_solution();
private:
	bool validate_route();
	bool follow_route(Node *node);
	std::shared_ptr<Puzzle> puzzle;
};

#endif
