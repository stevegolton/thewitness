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

/**
 * Creates a new puzzle solver for a given puzzle.
 *
 * @param[in]	puzzle	The puzzle to solve.
 */
PuzzleSolver::PuzzleSolver(std::shared_ptr<Puzzle> puzzle)
{
	this->puzzle = puzzle;
	validation_count = 0;
	node_count = 0;
	solutions_found = 0;
	id = 0;
	id2 = 0;
	m_prev_zone_count = 0;
}

/**
 * Returns the name of the solver as a string.
 *
 * @returns		Name of solver.
 */
std::string PuzzleSolver::get_name()
{
	return "Brute-Force Solver";
}

/**
 * Finds solutions to the puzzle.
 *
 * @param[in]	solutions	Maximum number of solutions to find, 0 = no limit.
 *
 * @return		true if any solutions were found, false otherwise.
 */
bool PuzzleSolver::find_solutions(int solutions_max)
{
	std::vector<Node>::iterator node;
	bool puzzle_is_solvable = false;		// Assume puzzle is unsolvable

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
		// Find solutions from this starting point
		solutions_found = follow_route(*entrypoint, solutions_max);

		// Check we found any solutions at all
		if(0 < solutions_found)
		{
			puzzle_is_solvable = true;
		}
	}

	return puzzle_is_solvable;
}

const unsigned int typemask = (path_node
		| path_node_required
		| path_node_entry
		| path_node_exit
		| path_way_vertical
		| path_way_horizontal
		| path_way_required_vertical
		| path_way_required_horizontal
		| face
		| face_square_white
		| face_square_black
		);

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
			if ((*path)->type & typemask)
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

int PuzzleSolver::flood_fill(Node *node, unsigned int type_mask, unsigned int type_count, int id)
{
	int step_count = 0;

	//printf("Searching\n");

	if (node->type & type_count) step_count++;
	node->id = id;

	std::vector<Node*>::iterator path;
	for (path = node->paths.begin(); path != node->paths.end(); path++)
	{
		//printf("Paths\n");
		if (((*path)->type & type_mask) && ((*path)->id != id) && (!(*path)->is_routed()))
		{
			//printf("Availible\n");
			step_count += flood_fill(*path, type_mask, type_count, id);
		}
	}

	return step_count;
}

const unsigned int faces = (
		face
		| face_square_black
		| face_square_white
		);

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

const unsigned int squares_mask = (
		face_square_black
		| face_square_white
		);

/**
 * Checks to see if the route we have taken so far is valid. Works on partial
 * and completed routes.
 *
 * @param[in]	node	Our current location.
 *
 * @returns		true if the route is valid, false otherwise.
 */
bool PuzzleSolver::validate_route(Node *current_node)
{
	int zone_count;
	//std::vector<Node*>::iterator node;

	return true;

	// Flood fill
	//printf("Flood fill = %d\n", flood_fill(current_node, faceable_typemask, face_typemask, id++));
	//flood_fill(current_node, faceable_typemask, face_typemask, id++);

	//if (current_node->paths.size() == 2)
	{
		//printf("wall\n");
		//zone_count = flood_fill(current_node, (paths | faces), faces, ++id);

		//if (zone_count != m_prev_zone_count)
		{
			// Search for an exit
			//if (0 == flood_fill(current_node, (paths | nodes), path_node_exit, ++id))
			{
			//	return false;
			}

			// Scan all the squares to see if they are in the completed region(s)
			std::vector<Node*>::iterator square;
			for(square = squares.begin(); square != squares.end(); square++)
			{
				//if ((*square)->id != id)
				{
					//printf("Square does not match??\n");
					// Flood fill to find more squares of this type
					if (0 != flood_fill(*square, (paths | faces), (squares_mask & ~(*square)->type), ++id))
					{
						return false;
					}
				}
			}

			//if (0 == flood_fill(current_node, (paths | nodes), path_node_exit, ++id))
			{
			//	return false;
			}
		}
	}

	return true;

#if 0
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
	else if((path_node == currentNode->type) || (path_node_exit == currentNode->type) || (path_node_entry == currentNode->type) || (path_node_required == currentNode->type))
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
				id2++;
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
	else
	{
		// Not a node, cannot possibly know if we're a winner
		return true;
	}

#endif
}

bool PuzzleSolver::find_squares(Node *node, unsigned int type)
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
		if ((*path)->type & (faces | paths))
		{
			//printf("Type is face or square or a pathway\n");
			// Check node isn't already routed and hasn't already been checked
			if (!(*path)->is_routed() && ((*path)->id2 != id2))
			{
				//printf("Painting %d -> %d\n", (*path)->id, id);
				// Mark the node to say it's been attacked by this flood fill
				// operation
				(*path)->id2 = id2;
				//printf("%d\n", id2);

				// Recurse into next node
				if(!find_squares(*path, type))
				{
					return false;
				}
			}
		}
	}

	return retval;
}

const unsigned int routeable_typemask = (path_node
		| path_node_required
		| path_node_entry
		| path_node_exit
		| path_way_vertical
		| path_way_horizontal
		| path_way_required_vertical
		| path_way_required_horizontal
		);

const unsigned int typemask_node = (path_node
		| path_node_required
		| path_node_entry
		| path_node_exit
		);

/**
 * Recursively calls itself to evaluate routes through the maze.
 *
 * @param[in]	node			Pointer to the node we are currently on.
 * @param[in]	solutions_max	Max number of solutions to find, 0 for all.
 */
int PuzzleSolver::follow_route(Node *node, int solutions_max)
{
	int solution_count = 0;
	std::vector<Node*>::iterator path;

	// Increment our node counter for debugging
	node_count ++;

	//PuzzlePrinter printer(puzzle);
	//printer.print_puzzle();

	// If the node is a "node" type (rather than a path), validate the solution
	// so far, maybe we have a winner!
	if (typemask_node & node->type)
	{
		if (validate_route(node))
		{
			if (path_node_exit == node->type)
			{
				// Found a solution
				return 1;
			}
		}
		else
		{
			// Route has already failed, backtrack
			return 0;
		}
	}

	// Search through all the available paths from this node
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
			solution_count += follow_route(*path, solutions_max);

			// Check we have found enough solutions, and get out leaving the
			// route in tact
			if ((0 != solutions_max) && (solution_count >= solutions_max)) break;

			// Backtrack  and clear the route
			node->set_route(nullptr);
		}
	}

	return solution_count;
}
