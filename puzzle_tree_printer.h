#ifndef PUZZLE_TREE_H
#define PUZZLE_TREE_H

#include <memory>
#include <string>

#include "puzzle.h"
#include "node.h"

class PuzzleTreePrinter
{
public:
	PuzzleTreePrinter(std::shared_ptr<Puzzle> puzzle);
	int print_tree();
private:
	int follow_route(Node *node);
	std::shared_ptr<Puzzle> puzzle;
	int coloffset;
	bool flipflop;
	bool flipflop_old;
};

#endif
