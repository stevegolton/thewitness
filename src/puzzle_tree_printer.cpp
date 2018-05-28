#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory>
#include <vector>
#include <string>

#include "puzzle_tree_printer.h"
#include "puzzle.h"
#include "node.h"

const unsigned int paths = (
		path_way_vertical
		| path_way_horizontal
		| path_way_required_vertical
		| path_way_required_horizontal
		);

const unsigned int nodes = (
		path_node
		| path_node_required
		| path_node_entry
		| path_node_exit
		);

/**
 * Creates a new puzzle solver for a given puzzle.
 *
 * @param[in]	puzzle	The puzzle to solve.
 */
PuzzleTreePrinter::PuzzleTreePrinter(std::shared_ptr<Puzzle> puzzle)
{
	this->puzzle = puzzle;
	this->coloffset = 0;
	this->flipflop_old = false;
	this->flipflop = false;
}

/**
 * Finds solutions to the puzzle.
 *
 * @param[in]	solutions	Maximum number of solutions to find, 0 = no limit.
 *
 * @return		true if any solutions were found, false otherwise.
 */
int PuzzleTreePrinter::print_tree()
{
	std::vector<Node>::iterator node;
	int id = 0;
	int sol_count;

	// First we prepare our puzzle for faster validation
	for(node = puzzle->pool.begin(); node != puzzle->pool.end(); node++)
	{
		//if (nodes & node->type)
			//node->name = 'A' + id++;
	}

	// First we prepare our puzzle for faster validation
	for(node = puzzle->pool.begin(); node != puzzle->pool.end(); node++)
	{
		// Capture all entry points
		if (path_node_entry == node->type)
		{
			// Find solutions from this starting point
			sol_count = follow_route(&(*node));
		}
	}

	return sol_count;
}

/**
 * Recursively calls itself to evaluate routes through the maze.
 *
 * @param[in]	node			Pointer to the node we are currently on.
 * @param[in]	solutions_max	Max number of solutions to find, 0 for all.
 */
int PuzzleTreePrinter::follow_route(Node *node)
{
	bool search = true;
	int sol_count = 0;

	if (nodes & node->type)
	{
		if (flipflop == true)
		{
			flipflop = false;
			printf("\n");
			for(int i=0; i<coloffset-1; i++)
			{
				printf("   ");
			}
			printf("  `");
		}

		printf("->%c", node->name);
		if (node->type == path_node_exit)
			search = false;

		coloffset ++;
	}

	if(search)
	{
		// Search through all the available paths from this node
		std::vector<Node*>::iterator path;
		for (path = node->paths.begin(); path != node->paths.end(); path++)
		{
			// Make sure the path type is a route-able one, and hasn't been routed
			// already
			if (    ((*path)->type & (nodes | paths))
				 && (!(*path)->is_routed()))
			{
				// Our route is now this path
				node->set_route(*path);

				// Follow this path
				sol_count += follow_route(*path);

				// Backtrack  and clear the route
				node->set_route(nullptr);
			}
		}
	}
	else
	{
		sol_count++;
	}

	if (nodes & node->type)
	{
		flipflop = true;
		coloffset --;
	}

	return sol_count;
}
