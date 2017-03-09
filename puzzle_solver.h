#ifndef PUZZLE_SOLVER_H_
#define PUZZLE_SOLVER_H_

#include "puzzle.h"
#include "sbuf.h"

int PUZZLESOLVER_SolvePuzzle(stPUZZLE_Node_t* node, stPUZZLE_Inst_t *puzzle, bool findone, stSBUF_instance_t *sbuf);

#endif /* PUZZLE_SOLVER_H_ */
