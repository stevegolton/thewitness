#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include <iostream>

#include <memory>
#include <vector>

#include "puzzle_printer.h"
#include "puzzle.h"

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

	// Print each node in the puzzle
	for(iter = puzzle->pool.begin(); iter != puzzle->pool.end(); iter++)
	{
		char printchar;

		if(iter->type == blank)
			continue;

		switch(iter->type)
		{
		case face:
			printchar = ' ';
			break;
		case path_node:
			printchar = '.';
			break;
		case path_way_horizontal:
			printchar = '-';
			break;
		case path_way_vertical:
			printchar = '|';
			break;
		case face_square_white:
			printchar = 'W';
			break;
		case face_square_black:
			printchar = 'B';
			break;
		default:
			printchar = '?';
		}

		if(iter->is_routed())
		{
			printchar = 'o';
		}

		sbuf[iter->x + (iter->y * x_max)] = printchar;
	}

#if 0
	for(required = puzzle->required.begin(); required != puzzle->required.end(); required++)
	{
		sbuf[(*required)->x + (*required)->y * x_max] = 'x';
	}

	// Print the route
	Node *printnode = puzzle->entry;

	// Run through all nodes and print them to the screen buffer
	while(printnode->is_routed())
	{

		/*
		sbuf[xavg + yavg * x_max] = linechar;

		sbuf[printnode->x + printnode->y * x_max] = 'o';

		char linechar = (printnode->x == printnode->get_route()->x)? '|' : '-';
		int xavg = (printnode->x + printnode->get_route()->x)/2;
		int yavg = (printnode->y + printnode->get_route()->y)/2;;
		sbuf[xavg + yavg * x_max] = linechar;

		// Move the print head on to the node in the route
		printnode = printnode->get_route();
		*/
	}
#endif

	sbuf[puzzle->entry->x + puzzle->entry->y * x_max] = 'O';
	sbuf[puzzle->exit->x + puzzle->exit->y * x_max] = '`';

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
