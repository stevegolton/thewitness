#include <iostream>
#include <memory>

#include "node.h"
#include "puzzle.h"
#include "puzzle_solver.h"
#include "grid_puzzle_factory.h"
#include "puzzle_printer.h"

int main(void)
{
	GridPuzzleFactory factory(8, 8);

	std::shared_ptr<Puzzle> pzl = factory.make_puzzle();
	pzl->require_node(&pzl->pool[1]);
	pzl->require_node(&pzl->pool[4]);
	pzl->require_node(&pzl->pool[5]);
	pzl->require_node(&pzl->pool[6]);

	PuzzlePrinter printer1(pzl);
	printer1.print_puzzle();

	PuzzleSolver solver(pzl);

	solver.find_one_solution();

	// Print the solution
	PuzzlePrinter printer(pzl);
	printer.print_puzzle();
}
