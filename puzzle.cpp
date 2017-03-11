#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "puzzle.h"

Puzzle::Puzzle(int node_count)
{
	this->pool.resize(node_count);
	this->entry = &pool[0];
	this->exit = &pool[node_count-1];
}

Puzzle::~Puzzle()
{
	// Nothing to do
}

void Puzzle::require_node(Node *node)
{
	this->required.push_back(node);
}
