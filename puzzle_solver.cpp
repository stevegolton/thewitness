#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory>
#include <vector>

#include "puzzle_solver.h"
#include "puzzle.h"
#include "node.h"

PuzzleSolver::PuzzleSolver(std::shared_ptr<Puzzle> puzzle)
{
	this->puzzle = puzzle;
}

void PuzzleSolver::find_one_solution()
{
	// Nothing to do
	std::cout << "Solving the puzzle, hang onto your panties!!" << std::endl;

	follow_route(puzzle->entry);
}

/**
 * Checks to see if the route in our puzzle is valid.
 *
 * @returns true if valid, false otherwise
 */
bool PuzzleSolver::validate_route()
{
	std::vector<Node*>::iterator iter;

	// Check all the required nodes have been routed
	for(iter = puzzle->required.begin(); iter != puzzle->required.end(); iter++)
	{
		if(false == (*iter)->is_routed())
		{
			// Node not routed, get out, this puzzle is bad
			return false;
		}
	}

	// We got to the end and there were no errors so we can assume the puzzle
	// is valid! :)
	return true;
}

bool PuzzleSolver::follow_route(Node *node)
{
	int solution_count = 0;
	int nodeidx;
	std::vector<Node*>::iterator path;

	// If we are looking at the exit node, we have a complete route
	if(node == puzzle->exit)
	{
		// We have reached the end node, a solution has been found, validate the solution
		if(validate_route())
		{
			printf("Found a solution!\n");
			solution_count++;
		}
	}
	else
	{
		// Search for non NULL and non-visited paths
		for (path = node->paths.begin(); path != node->paths.end(); path++)
		{
			if (!(*path)->is_routed())
			{
				// Temporarily set the route to be this this path, and
				node->set_route(*path);
				solution_count += follow_route(*path);

				// We only need to find one
				if (solution_count == 1) break;

				// Clear the route
				node->set_route(nullptr);
			}
		}
	}

	return solution_count;
}
