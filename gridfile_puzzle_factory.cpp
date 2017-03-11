#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string>		// std::string

#include "gridfile_puzzle_factory.h"
#include "puzzle.h"
#include "node.h"

GridFilePuzzleFactory::GridFilePuzzleFactory(std::string filename)
{
	this->filename = filename;
}

std::shared_ptr<Puzzle> GridFilePuzzleFactory::make_puzzle()
{
	const int gridsize = 20;

	std::shared_ptr<Puzzle> puzzle = std::make_shared<Puzzle>(gridsize*gridsize);
	int x = 0;
	int y = 0;
	char c;
	FILE * file;

	file = fopen( filename.c_str() , "r");

	if (file)
	{
		while ((c = fgetc(file)) != EOF)
		{
			Node *node = &puzzle->pool[(x) + (y)*gridsize];

			// Just go ahead and pre-make all the connections!
			if(x > 0)             node->add_path(&puzzle->pool[(x-1) + (y)*gridsize]);
			if(x < (gridsize-1))  node->add_path(&puzzle->pool[(x+1) + (y)*gridsize]);
			if(y > 0)             node->add_path(&puzzle->pool[(x) + (y-1)*gridsize]);
			if(y < (gridsize-1))  node->add_path(&puzzle->pool[(x) + (y+1)*gridsize]);

			//printf("%d %d\n", x, y);

			switch(c)
			{
			case 'O':
				node->x = x;
				node->y = y;
				node->type = path_node_entry;
				puzzle->entry = node; // TODO deprecate this...
				x++;
				break;
			case '`':
				node->x = x;
				node->y = y;
				node->type = path_node_exit;
				x++;
				puzzle->exit = node; // TODO deprecate this...
				break;
			case '|':
				node->x = x;
				node->y = y;
				node->type = path_way_vertical;
				x++;
				break;
			case '-':
				node->x = x;
				node->y = y;
				node->type = path_way_horizontal;
				x++;
				break;
			case '.':
				node->x = x;
				node->y = y;
				node->type = path_node;
				x++;
				break;
			case ' ':
				node->x = x;
				node->y = y;
				node->type = face;
				x++;
				break;
			case 'W':
				node->x = x;
				node->y = y;
				node->type = face_square_white;
				x++;
				break;
			case 'B':
				node->x = x;
				node->y = y;
				node->type = face_square_black;
				x++;
				break;
			case 'X':
				node->x = x;
				node->y = y;
				node->type = path_node_required;
				puzzle->require_node(node);
				x++;
				break;
			case 'x':
				node->x = x;
				node->y = y;
				node->type = path_way_required_vertical; // Doesn't actually matter the orientation...
				puzzle->require_node(node);
				x++;
				break;
			case '\n':
				y++;
				x = 0;
				break;
			default:
				// TODO
				break;
			}

			//printf("node->type = %d\n", node->type);
		}
		fclose(file);
	}

	return puzzle;
}
