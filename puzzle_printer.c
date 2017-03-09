#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "puzzle_printer.h"
#include "puzzle.h"
#include "sbuf.h"

// TODO move to puzzle printer class
void PUZZLEPRINTER_PrintPuzzle(stPUZZLE_Inst_t *puzzle, stSBUF_instance_t *sbuf)
{
	int i;

	// Draw a period for every node
	for (i = 0; i < puzzle->iNodeCount; i++)
	{
		SBUF_SetChar(sbuf, puzzle->pastNodePool[i].xPos, puzzle->pastNodePool[i].yPos, '.');
	}

	// Print the required nodes as x's
	stPUZZLE_Node_t** head = &puzzle->pastRequiredNodes[0];
	while (NULL != *head)
	{
		SBUF_SetChar(sbuf, (*head)->xPos, (*head)->yPos, 'x');
		head++;
	}
}
