#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

#include "sbuf.h"
#include "puzzle.h"
#include "grid_puzzle_factory.h"
#include "puzzle_printer.h"
#include "puzzle_solver.h"

// Describes the dimensions of the screen buffer character array
#define SBUF_WIDTH 50
#define SBUF_HEIGHT 16

// Main entry point
int main(void)
{
	stSBUF_instance_t *pScreen = SBUF_New(SBUF_WIDTH, SBUF_HEIGHT);

	// Let's make ourselves a grid puzzle
	stPUZZLE_Inst_t *pPuzzle = GRIDPUZZLEFACTORY_MakeGridPuzzle(8, 8);
	PUZZLE_RequireNode(pPuzzle, &pPuzzle->pastNodePool[1]);
	PUZZLE_RequireNode(pPuzzle, &pPuzzle->pastNodePool[4]);
	PUZZLE_RequireNode(pPuzzle, &pPuzzle->pastNodePool[5]);
	PUZZLE_RequireNode(pPuzzle, &pPuzzle->pastNodePool[6]);
	PUZZLE_RequireNode(pPuzzle, &pPuzzle->pastNodePool[12]);

	// Print the grid
	SBUF_Clear(pScreen);
	PUZZLEPRINTER_PrintPuzzle(pPuzzle, pScreen);
	SBUF_Print(pScreen);

	// Start by looking at the first node
	int solutions = PUZZLESOLVER_SolvePuzzle(pPuzzle->pstEntry, pPuzzle, true, pScreen);

	// Mr clean
	SBUF_Delete(pScreen);
	PUZZLE_Delete(pPuzzle);

	// Print the number of solutions found
	printf("solutions = %d\n", solutions);	

	return 0;
}
