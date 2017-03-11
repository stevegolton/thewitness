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

bool PuzzleSolver::find_one_solution()
{
	// Nothing to do
	std::cout << "Solving using the brute force solver :)" << std::endl;

	if(0 != follow_route(puzzle->entry))
	{
		return true;
	}
}

/**
 * Checks to see if the route in our puzzle is valid.
 *
 * @returns true if valid, false otherwise
 */
bool PuzzleSolver::validate_route()
{
	std::vector<Node*>::iterator iter;

	//printf("Validating puzzle...\n");

	// Check all the required nodes have been routed
	for(iter = puzzle->required.begin(); iter != puzzle->required.end(); iter++)
	{
		//printf("Required\n");
		if(false == (*iter)->is_routed())
		{
			// Node not routed, get out, this puzzle is bad
			return false;
		}
	}

	// Now, starting at each face type
	std::vector<Node>::iterator node;

	// Print each node in the puzzle
	for(node = puzzle->pool.begin(); node != puzzle->pool.end(); node++)
	{
		if (node->type == face_square_white)
		{
			//printf("We found a square!\n");

			// Flood fill to find more squares of this type
			if(!find_squares(&(*node), node->type))
			{
				return false;
			}
		}
	}

	// We got to the end and there were no errors so we can assume the puzzle
	// is valid! :)
	return true;
}

bool PuzzleSolver::find_squares(Node *node, enum nodetype type)
{
	bool retval = true;

	//printf("Type is %d and col is %d\n", node->type, node->col);
	if (    (node->type == face_square_black)
	     || (node->type == face_square_white) )
	{
		if (node->type != type)
		{
			// We have a square colour mismatch... gahh
			//printf("!!Bad colour!!\n");
			return false;
		}
	}

	// Iterate over each path in the node
	std::vector<Node*>::iterator path;
	for (path = node->paths.begin(); path != node->paths.end(); path++)
	{
		//printf("Checking a path %d\n", (*path)->type);
		if (    ((*path)->type == face)
		     || ((*path)->type == face_square_black)
			 || ((*path)->type == face_square_white)
			 || ((*path)->type == path_way_vertical)
			 || ((*path)->type == path_way_horizontal)
			 || ((*path)->type == path_way_required_vertical)
			 || ((*path)->type == path_way_required_horizontal))
		{
			//printf("Type is face or square or a pathway\n");
			// Check node isn't already routed
			if (!(*path)->is_routed())
			{
				// Yay we can route to it!
				node->set_route(*path);
				retval = find_squares(*path, type);
				node->set_route(nullptr);

				if(!retval)
				{
					break;
				}
			}
		}
	}

	return retval;
}

int PuzzleSolver::follow_route(Node *node)
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
			//printf("Found a solution!\n");
			solution_count++;
		}
	}
	else
	{
		// Search for non NULL and non-visited paths
		for (path = node->paths.begin(); path != node->paths.end(); path++)
		{
			// Make sure the path type is one we can access
			if (    ((*path)->type == path_node)
			     || ((*path)->type == path_node_entry)
				 || ((*path)->type == path_node_exit)
				 || ((*path)->type == path_way_vertical)
				 || ((*path)->type == path_way_horizontal)
				 || ((*path)->type == path_node_required)
				 || ((*path)->type == path_way_required_vertical)
				 || ((*path)->type == path_way_required_horizontal))
			{
				// Ensure the path isn't already routed
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
	}

	return solution_count;
}
