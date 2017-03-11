#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include "node.h"

class Puzzle
{
public:
	Puzzle(int node_count);
	~Puzzle();
	void require_node(Node *node);

	Node *entry;
	Node *exit;
	std::vector<Node> pool;
	std::vector<Node*> required;
private:

};

#endif
