#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "grid_puzzle_factory.h"
#include "puzzle.h"

// Creates a gird of dimensions width and height.
// The starting node is at (0, 0), and the exit node is at (width-1, height-1).
// TODO make it so that the entry and exit points can be changed!
stPUZZLE_Inst_t *GRIDPUZZLEFACTORY_MakeGridPuzzle(int cols, int rows)
{
	stPUZZLE_Inst_t *pstPuzzle = PUZZLE_New(cols*rows);

	if(NULL == pstPuzzle)
	{
		return NULL;
	}

	// Go through each node in the grid and assign its x & y positions as well as its neighbouring nodes as connections.
	int x, y, i;
	for(y=0; y<rows; y++)
	{
		for(x=0; x<cols; x++)
		{
			stPUZZLE_Node_t *pstNode = &pstPuzzle->pastNodePool[x + y*cols];
			PUZZLE_SetNodePosition(pstNode, x*2, y*2);

			// Add connections to neighbouring nodes
			if(x > 0)        PUZZLE_MakeConnection(pstNode, &pstPuzzle->pastNodePool[(x-1) + (y)*cols]);
			if(x < (cols-1)) PUZZLE_MakeConnection(pstNode, &pstPuzzle->pastNodePool[(x+1) + (y)*cols]);
			if(y > 0)        PUZZLE_MakeConnection(pstNode, &pstPuzzle->pastNodePool[(x) + (y-1)*cols]);
			if(y < (rows-1)) PUZZLE_MakeConnection(pstNode, &pstPuzzle->pastNodePool[(x) + (y+1)*cols]);
		}
	}

	// Set the start and end nodes
	pstPuzzle->pstEntry = &pstPuzzle->pastNodePool[0];
	pstPuzzle->pstExit = &pstPuzzle->pastNodePool[(cols*rows) - 1];

	return pstPuzzle;
}
