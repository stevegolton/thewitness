#include <iostream>
#include <memory>
#include <climits>

#include "node.h"
#include "puzzle.h"
#include "puzzle_solver.h"
#include "grid_puzzle_factory.h"
#include "gridfile_puzzle_factory.h"
#include "puzzle_printer.h"

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage = %s <filename>\n", argv[0]);
		return 1;
	}

	std::cout << "Loading puzzle from " << argv[1] << std::endl;

	GridFilePuzzleFactory factory(argv[1]);
	std::shared_ptr<Puzzle> pzl = factory.make_puzzle();

	std::cout << "Puzzle loaded:" << std::endl;
	PuzzlePrinter printer1(pzl);
	printer1.print_puzzle();

	std::cout << "Solving, this may take a while..." << std::endl;

	PuzzleSolver solver(pzl);
	solver.find_solutions(LONG_MAX);

	printf("%lu steps, %lu candiadates, %lu solutions\n", solver.node_count, solver.validation_count, solver.solution_count_glob);

	if(solver.find_one_solution())
	{
		std::cout << "Printing just one solution:" << std::endl;
		// Print the solution
		PuzzlePrinter printer(pzl);
		printer.print_puzzle();
	}
	else
	{
		std::cout << "No solutions found... :(" << std::endl;
	}
}
