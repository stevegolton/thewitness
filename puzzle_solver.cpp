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
	std::vector<Node>::iterator node;
	std::cout << "Solving using the brute force solver :)" << std::endl;

	// First we prepare our puzzle for faster validation
	for(node = puzzle->pool.begin(); node != puzzle->pool.end(); node++)
	{
		// Capture all the required nodes
		if (    (path_way_required_vertical == node->type)
		     || (path_way_required_horizontal == node->type)
		     || (path_node_required == node->type))
		{
			required.push_back(&(*node));
		}
		// Capture all the square faces
		else if (    (face_square_white == node->type)
		          || (face_square_black == node->type))
		{
			squares.push_back(&(*node));
		}
		// Capture all entry points
		else if (path_node_entry == node->type)
		{
			entrypoints.push_back(&(*node));
		}
	}

	// Try all entry points
	std::vector<Node*>::iterator entrypoint;
	for(entrypoint = entrypoints.begin(); entrypoint != entrypoints.end(); entrypoint++)
	{
		if(0 != follow_route(*entrypoint))
		{
			return true;
		}
	}

	return false;
}

/**
 * Checks to see if the route in our puzzle is valid.
 *
 * @returns true if valid, false otherwise
 */
bool PuzzleSolver::validate_route()
{
	std::vector<Node*>::iterator node;

	//printf("Validating puzzle...\n");

	// Check all the required nodes have been routed
	for(node = required.begin(); node != required.end(); node++)
	{
		//printf("Required\n");
		if(false == (*node)->is_routed())
		{
			// Node not routed, get out, this puzzle is bad
			return false;
		}
	}

	// Print each node in the puzzle
	for(node = squares.begin(); node != squares.end(); node++)
	{
		// Flood fill to find more squares of this type
		if(!find_squares(*node, (*node)->type))
		{
			return false;
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
	if(path_node_exit == node->type)
	{
		//printf("Found a potential route, validating...\n");

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
			if (    ((*path)->type == path_node_required)
				 || ((*path)->type == path_way_required_vertical)
				 || ((*path)->type == path_way_required_horizontal)
				 || ((*path)->type == path_node_exit))
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

		if (solution_count == 1) return solution_count;

		// Search for non NULL and non-visited paths
		for (path = node->paths.begin(); path != node->paths.end(); path++)
		{
			// Make sure the path type is one we can access
			if (    ((*path)->type == path_node)
				 || ((*path)->type == path_node_entry)
				 || ((*path)->type == path_way_vertical)
				 || ((*path)->type == path_way_horizontal))
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
