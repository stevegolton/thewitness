#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include <iostream>

#include <memory>
#include <vector>

#include "puzzle_printer.h"
#include "puzzle.h"
#include "sbuf.h"

PuzzlePrinter::PuzzlePrinter(std::shared_ptr<Puzzle> puzzle_to_print)
{
	x_max = 0;
	y_max = 0;

	this->puzzle = puzzle_to_print;

	std::vector<Node>::iterator iter;

	// Check how large our buffer should be
	for(iter = puzzle->pool.begin(); iter != puzzle->pool.end(); iter++)
	{
		if (iter->x > x_max)
			x_max = iter->x;
		if (iter->y > y_max)
			y_max = iter->y;
	}

	x_max++;
	y_max++;

	// TODO be more C++!
	sbuf = (char*)malloc(sizeof(char) * x_max * y_max);
	memset(sbuf, ' ', sizeof(char) * x_max * y_max);
}

PuzzlePrinter::~PuzzlePrinter()
{
	free(sbuf);
}

void PuzzlePrinter::print_puzzle()
{
	std::vector<Node>::iterator iter;
	std::vector<Node*>::iterator required;

	for(iter = puzzle->pool.begin(); iter != puzzle->pool.end(); iter++)
	{
		sbuf[iter->x + (iter->y * x_max)] = '.';
	}

	for(required = puzzle->required.begin(); required != puzzle->required.end(); required++)
	{
		sbuf[(*required)->x + (*required)->y * x_max] = 'x';
	}

	// Print the route
	Node *printnode = puzzle->entry;

	// Run through all nodes and print them to the screen buffer
	while(printnode->is_routed())
	{
		sbuf[printnode->x + printnode->y * x_max] = 'o';

		char linechar = (printnode->x == printnode->get_route()->x)? '|' : '-';
		int xavg = (printnode->x + printnode->get_route()->x)/2;
		int yavg = (printnode->y + printnode->get_route()->y)/2;;
		sbuf[xavg + yavg * x_max] = linechar;

		// Move the print head on to the node in the route
		printnode = printnode->get_route();
	}

	sbuf[puzzle->entry->x + puzzle->entry->y * x_max] = 'S';
	sbuf[puzzle->exit->x + puzzle->exit->y * x_max] = 'E';

	// Print the screen buffer to stdout
	for(int y = 0; y < y_max; y++)
	{
		for(int x = 0; x < x_max; x++)
		{
			printf("%c", sbuf[x + (y * x_max)]);
			//printf("x");
		}
		printf("\n");
	}
}
