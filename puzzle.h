#ifndef PUZZLE_H_
#define PUZZLE_H_

typedef struct node stPUZZLE_Node_t;

// This struct defines a node in a grid. It has an array of pointers to other nodes which are the nodes it can route to.
// The route is a pointer to the currently routed node or NULL if the node has not been visited yet.
// The x and y values are the positions of the node in the grid, and are only used for printing the grid, not for solving.
struct node
{
	stPUZZLE_Node_t *apstCxns[4]; // TODO make this variable
	int iCxnCount;
	stPUZZLE_Node_t *pstRoute;
	int xPos;
	int yPos;
};

// This struct defines an entire grid with one entry point and exit point.
// The start and end pointers point to the entry and exit nodes respectively.
// The pool pointer points to the start of the pool of nodes which must be allocated manually.
typedef struct
{
	stPUZZLE_Node_t *pstEntry;
	stPUZZLE_Node_t *pstExit;
	stPUZZLE_Node_t *pastNodePool;
	int iNodeCount;
	stPUZZLE_Node_t *pastRequiredNodes[100]; // TODO make the variable
	int iReqiredNodesCount;

} stPUZZLE_Inst_t;

stPUZZLE_Inst_t *PUZZLE_New(int iNodeCount);
void PUZZLE_SetNodePosition(stPUZZLE_Node_t *pstNode, int iX, int iY);
void PUZZLE_MakeConnection(stPUZZLE_Node_t *pstParent, stPUZZLE_Node_t *pstChild);
void PUZZLE_RequireNode(stPUZZLE_Inst_t *pstPuzzle, stPUZZLE_Node_t *pstNode);
void PUZZLE_Delete(stPUZZLE_Inst_t *pstPuzzle);

#endif /* PUZZLE_H_ */
