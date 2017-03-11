#include <iostream>
#include <memory>

#include "node.h"
#include "puzzle.h"
#include "puzzle_solver.h"
#include "grid_puzzle_factory.h"
#include "gridfile_puzzle_factory.h"
#include "puzzle_printer.h"

int main(void)
{
	std::cout << "Making a puzzle" << std::endl;

	GridFilePuzzleFactory factory("example1");
	std::shared_ptr<Puzzle> pzl = factory.make_puzzle();

	std::cout << "Solving..." << std::endl;

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
