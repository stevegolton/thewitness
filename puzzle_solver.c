#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>

#include "puzzle_solver.h"
#include "puzzle.h"
#include "sbuf.h"
#include "puzzle_printer.h"

// TODO move to puzzle solver class
bool validate_route(stPUZZLE_Inst_t *puzzle)
{
	stPUZZLE_Node_t **head = &puzzle->pastRequiredNodes[0];

	while(NULL != *head)
	{
		// Ensure the node is routed
		if(NULL == (*head)->pstRoute)
		{
			return false;
		}

		head++;
	}

	return true;
}

// Work through all the connecting nodes starting at a particular node
// Recursively calls do_node() on all connecting nodes which haven't been visited yet
int PUZZLESOLVER_SolvePuzzle(stPUZZLE_Node_t* node, stPUZZLE_Inst_t *puzzle, bool findone, stSBUF_instance_t *sbuf)
{
	int solution_count = 0;
	int nodeidx;
	stPUZZLE_Node_t *printnode;

	if(node == puzzle->pstExit)
	{
		// We have reached the end node, a solution has been found, validate the solution
		if(validate_route(puzzle))
		{
			printf("Found a solution\n");

			solution_count++;

			// The node we are currently printing is the start node
			printnode = puzzle->pstEntry;

			// Clear the screen buffer
			SBUF_Clear(sbuf);

			PUZZLEPRINTER_PrintPuzzle(puzzle, sbuf);

			// Run through all nodes and print them to the screen buffer
			while(NULL != printnode)
			{
				// Switch on the type of node we are dealing with
				if(puzzle->pstEntry == printnode)
					SBUF_SetChar(sbuf, printnode->xPos, printnode->yPos, 'S');
				else if(puzzle->pstExit == printnode)
					SBUF_SetChar(sbuf, printnode->xPos, printnode->yPos, 'E');
				else
					SBUF_SetChar(sbuf, printnode->xPos, printnode->yPos, 'o');

				// Put a line between this and the next route node
				if(printnode->pstRoute != NULL)
				{
					char linechar = (printnode->xPos == printnode->pstRoute->xPos)? '|' : '-';
					SBUF_SetChar(sbuf, (printnode->xPos + printnode->pstRoute->xPos)/2, (printnode->yPos + printnode->pstRoute->yPos)/2, linechar);
				}

				// Move the print node on to the next in the route
				printnode = printnode->pstRoute;
			}
			// Print the screen buffer to stdout
			SBUF_Print(sbuf);
		}
	}
	else
	{
		// Search for non NULL and non-visited connecting nodes
		for(nodeidx=0; nodeidx<4; nodeidx++)
		{
			if ((node->apstCxns[nodeidx] != NULL) && (node->apstCxns[nodeidx]->pstRoute == NULL))
			{
				// Temporarily set the route to be this node then call do_node on it
				node->pstRoute = node->apstCxns[nodeidx];
				solution_count += PUZZLESOLVER_SolvePuzzle(node->apstCxns[nodeidx], puzzle, findone, sbuf);
				if (solution_count == 1 && findone) break;
				node->pstRoute = NULL;
			}
		}
	}

	return solution_count;
}
