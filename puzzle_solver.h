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
	bool find_solutions(unsigned long solutions);
	unsigned long validation_count;
	unsigned long node_count;
	unsigned long solution_count_glob;
private:
	bool validate_route();
	unsigned long follow_route(Node *node, unsigned long solutions);
	bool find_squares(Node *node, enum nodetype type);
	std::shared_ptr<Puzzle> puzzle;
	std::vector<Node*> required;
	std::vector<Node*> squares;
	std::vector<Node*> entrypoints;
};

#endif
