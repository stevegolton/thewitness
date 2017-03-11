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
	int width = (cols*2)-1;
	int height = (rows*2)-1;
	int x, y;
	std::shared_ptr<Puzzle> puzzle = std::make_shared<Puzzle>(width * height);

	// Go through each node in the grid and assign its x & y positions as well
	// as its neighbouring nodes as connections.
	for(y=0; y<height; y++)
	{
		for(x=0; x<width; x++)
		{
			// Grab our node from the node pool
			Node *node = &puzzle->pool[x + y*width];

			// Set the node's position on the grid
			node->x = x;
			node->y = y;

			// Add connections to neighbouring nodes
			if(x > 0)        node->add_path(&puzzle->pool[(x-1) + (y)*width]);
			if(x < (width-1)) node->add_path(&puzzle->pool[(x+1) + (y)*width]);
			if(y > 0)        node->add_path(&puzzle->pool[(x) + (y-1)*width]);
			if(y < (height-1)) node->add_path(&puzzle->pool[(x) + (y+1)*width]);

			if((x%2 == 1) && (y%2 == 1))
			{
				node->type = face;
			}
			else
			{
				if((x%2 == 0) && (y%2 == 0))
				{
					node->type = path_node;
				}
				else
				{
					node->type = path_way;
				}
			}
		}
	}

	// Set the start and end nodes
	puzzle->entry = &puzzle->pool[0];
	puzzle->exit = &puzzle->pool[(width*height) - 1];

	return puzzle;
}
