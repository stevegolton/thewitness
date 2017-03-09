#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "puzzle.h"

stPUZZLE_Inst_t *PUZZLE_New(int iNodeCount)
{
	stPUZZLE_Inst_t *pstPuzzle = (stPUZZLE_Inst_t*)malloc(sizeof(stPUZZLE_Inst_t));

	if(NULL == pstPuzzle)
		return NULL;

	memset(pstPuzzle, 0, sizeof(stPUZZLE_Inst_t));
	pstPuzzle->pastNodePool = (stPUZZLE_Node_t*)malloc(sizeof(stPUZZLE_Node_t) * iNodeCount);

	if(NULL == pstPuzzle->pastNodePool)
	{
		free(pstPuzzle);
		return NULL;
	}

	// Reset pool & store nodecount
	memset(pstPuzzle->pastNodePool, 0, sizeof(stPUZZLE_Node_t) * iNodeCount);
	pstPuzzle->iNodeCount = iNodeCount;

	return pstPuzzle;
}

void PUZZLE_Delete(stPUZZLE_Inst_t *pstPuzzle)
{
	if((NULL != pstPuzzle) && (NULL != pstPuzzle->pastNodePool))
		free(pstPuzzle->pastNodePool);

	if(NULL != pstPuzzle)
		free(pstPuzzle);

	return;
}

void PUZZLE_SetNodePosition(stPUZZLE_Node_t *pstNode, int iX, int iY)
{
	pstNode->xPos = iX;
	pstNode->yPos = iY;
	return;
}

void PUZZLE_MakeConnection(stPUZZLE_Node_t *pstParent, stPUZZLE_Node_t *pstChild)
{
	pstParent->apstCxns[pstParent->iCxnCount++] = pstChild;
	return;
}

void PUZZLE_RequireNode(stPUZZLE_Inst_t *pstPuzzle, stPUZZLE_Node_t *pstNode)
{
	pstPuzzle->pastRequiredNodes[pstPuzzle->iReqiredNodesCount++] = pstNode;
	return;
}
