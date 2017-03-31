#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory>
#include <vector>
#include <string>

#include "puzzle_solver.h"
#include "puzzle.h"
#include "node.h"
#include "puzzle_printer.h"

PuzzleSolver::PuzzleSolver(std::shared_ptr<Puzzle> puzzle)
{
	this->puzzle = puzzle;
	validation_count = 0;
	node_count = 0;
	solution_count_glob = 0;
	id = 0;
}

bool PuzzleSolver::find_solutions(unsigned long solutions)
{
	std::vector<Node>::iterator node;

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
		if(0 != follow_route(*entrypoint, solutions))
		{
			return true;
		}
	}

	return false;
}

/**
 * Shortcut method to find one solution.
 *
 * @returns		true if a solution has been found, false otherwise.
 */
bool PuzzleSolver::find_one_solution()
{
	return find_solutions(1);
}

/**
 * Returns the name of the solver.
 *
 * @returns		Name of solver.
 */
std::string PuzzleSolver::get_name()
{
	return "Brute-force solver";
}

bool PuzzleSolver::check_for_exit(Node *node)
{
	bool retval = false;

	if(node->type == path_node_exit)
	{
		// We are already at an exit. No need to go on!
		retval = true;
	}
	else
	{
		// Flood fill starting from a given node looking for exit nodes
		// Iterate over each path in the node
		std::vector<Node*>::iterator path;
		for (path = node->paths.begin(); path != node->paths.end(); path++)
		{
			// Otherwise, flood fill all the route-able nodes to see if there's
			// ANY chance we will be able to get to an exit node
			if (    ((*path)->type == path_node)
				 || ((*path)->type == path_node_required)
				 || ((*path)->type == path_node_entry)
				 || ((*path)->type == path_node_exit)
				 || ((*path)->type == path_way_vertical)
				 || ((*path)->type == path_way_horizontal)
				 || ((*path)->type == path_way_required_vertical)
				 || ((*path)->type == path_way_required_horizontal)
				 || ((*path)->type == face)
				 || ((*path)->type == face_square_white)
				 || ((*path)->type == face_square_black)
				)
			{
				// Check node isn't already routed and hasn't already been checked
				if (!(*path)->is_routed() && ((*path)->id != id))
				{
					//printf("Painting %d -> %d\n", (*path)->id, id);
					// Mark the node to say it's been attacked by this flood fill
					// operation
					(*path)->id = id;

					// Recurse into next node
					if(check_for_exit(*path))
					{
						retval = true;
					}
				}
			}
		}
	}

	return retval;
}

/**
 * Checks to see if the route we have taken so far is valid. Works on partial
 * and completed routes.
 *
 * @param[in]	node	Our current location.
 *
 * @returns		true if the route is valid, false otherwise.
 */
bool PuzzleSolver::validate_route(Node *currentNode)
{
	std::vector<Node*>::iterator node;

	//printf("Validating puzzle...\n");

	// First of all we check to see if this is a partial solution or a full one
	if(path_node_exit == currentNode->type)
	{
		validation_count++;
		// It is a full one - validate properly
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

		// Check all squares are in a valid place
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
	else
	{
		// It is a partial one - validate partially
		id++;
		if(check_for_exit(currentNode))
		{
			//PuzzlePrinter printer(puzzle);
			//printer.print_puzzle();

			// Scan all the squares to see if they are in the completed region(s)
			std::vector<Node*>::iterator square;
			for(square = squares.begin(); square != squares.end(); square++)
			{
				if ((*square)->id != id)
				{
					//printf("Square does not match??\n");
					// Flood fill to find more squares of this type
					if(!find_squares(*square, (*square)->type))
					{
						return false;
					}
				}
			}

			return true;
		}
		else
			return false;
	}
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

/**
 * Recursively calls itself to evaluate routes through the maze.
 *
 * @param[in]	node		Pointer the node we are currently on.
 * @param[in]	solCount	Number of solutions to stop at, or 0 for all.
 */
int PuzzleSolver::follow_route(Node *node, int solCount)
{
	int solution_count = 0;
	int nodeidx;
	std::vector<Node*>::iterator path;

	// Increment our local node counter
	node_count ++;

	// If we are looking at the exit node, we have a complete route
	if(path_node_exit == node->type)
	{
		// We have reached the end node, a solution has been found, validate the solution
		if(validate_route(node))
		{
			//printf("Found a solution!\n");
			solution_count++;
			solution_count_glob++;
		}
	}
	else
	{
		// First of all, validate the partial route
		if(validate_route(node))
		{
			// Search through all paths availible to this node
			for (path = node->paths.begin(); path != node->paths.end(); path++)
			{
				// Make sure the path type is one we can access
				if (    ((*path)->type == path_node_required)
					 || ((*path)->type == path_way_required_vertical)
					 || ((*path)->type == path_way_required_horizontal)
					 || ((*path)->type == path_node_exit)
					 || ((*path)->type == path_node)
					 || ((*path)->type == path_node_entry)
					 || ((*path)->type == path_way_vertical)
					 || ((*path)->type == path_way_horizontal))
				{
					// Ensure the path isn't already routed
					if (!(*path)->is_routed())
					{
						//printf("%p\n", (*path));

						// Set the route to be this this path
						node->set_route(*path);

						// Recursively call this method again on this new node
						solution_count += follow_route(*path, solCount);

						// Check we have found enough solutions, and get out
						if ((0 != solCount) && (solution_count >= solCount)) break;

						// Clear the route
						node->set_route(nullptr);
					}
				}
			}
		}
	}

	return solution_count;
}
