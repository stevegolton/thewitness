#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "grid_puzzle_factory.h"
#include "puzzle.h"

GridPuzzleFactory::GridPuzzleFactory(int cols, int rows)
{
	this->cols = cols;
	this->rows = rows;
}

std::shared_ptr<Puzzle> GridPuzzleFactory::make_puzzle()
{
	std::shared_ptr<Puzzle> puzzle = std::make_shared<Puzzle>(cols * rows);
	int x, y, i;

	// Go through each node in the grid and assign its x & y positions as well
	// as its neighbouring nodes as connections.
	for(y=0; y<rows; y++)
	{
		for(x=0; x<cols; x++)
		{
			Node *node = &puzzle->pool[x + y*cols];

			// Set the node's position
			node->x = x*2;
			node->y = y*2;

			// Add connections to neighbouring nodes
			if(x > 0)        node->add_path(&puzzle->pool[(x-1) + (y)*cols]);
			if(x < (cols-1)) node->add_path(&puzzle->pool[(x+1) + (y)*cols]);
			if(y > 0)        node->add_path(&puzzle->pool[(x) + (y-1)*cols]);
			if(y < (rows-1)) node->add_path(&puzzle->pool[(x) + (y+1)*cols]);
		}
	}

	// Set the start and end nodes
	puzzle->entry = &puzzle->pool[0];
	puzzle->exit = &puzzle->pool[(cols*rows) - 1];

	return puzzle;
}
