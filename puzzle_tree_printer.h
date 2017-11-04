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
	int leaf_count;
	int leaf_count_correct;
private:
	int flood_fill(Node *node, unsigned int type_mask, unsigned int type_count, int id);
	int follow_route(Node *node);
	std::shared_ptr<Puzzle> puzzle;
	int indent;
	bool newline;
	int id;
};

#endif
