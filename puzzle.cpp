#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "puzzle.h"

Puzzle::Puzzle(int node_count)
{
	this->pool.resize(node_count);
}

Puzzle::~Puzzle()
{
	// Nothing to do
}
