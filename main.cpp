#include <iostream>
#include <memory>

#include "node.h"
#include "puzzle.h"
#include "puzzle_solver.h"
#include "grid_puzzle_factory.h"
#include "puzzle_printer.h"

int main(void)
{
	GridPuzzleFactory factory(3, 3);

	std::shared_ptr<Puzzle> pzl = factory.make_puzzle();
	//pzl->require_node(&pzl->pool[1]);
	//pzl->require_node(&pzl->pool[4]);
	//pzl->require_node(&pzl->pool[5]);
	//pzl->require_node(&pzl->pool[6]);

	pzl->pool[6].type = square;
	pzl->pool[6].col = white;
	pzl->pool[8].type = square;
	pzl->pool[8].col = black;

	pzl->pool[16].type = square;
	pzl->pool[16].col = white;
	pzl->pool[18].type = square;
	pzl->pool[18].col = black;

	PuzzlePrinter printer1(pzl);
	printer1.print_puzzle();

	PuzzleSolver solver(pzl);

	if(solver.find_one_solution())
	{
		// Print the solution
		PuzzlePrinter printer(pzl);
		printer.print_puzzle();
	}
	else
	{
		std::cout << "No solutions found... :(" << std::endl;
	}
}
