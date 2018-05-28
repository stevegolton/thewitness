#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include "node.h"

class Puzzle
{
public:
	Puzzle(int node_count);
	~Puzzle();
	std::vector<Node> pool;
private:
};

#endif
