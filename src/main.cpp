#include <iostream>
#include <memory>
#include <climits>

#include "node.h"
#include "puzzle.h"
#include "puzzle_solver.h"
#include "grid_puzzle_factory.h"
#include "gridfile_puzzle_factory.h"
#include "puzzle_printer.h"
#include "puzzle_tree_printer.h"

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

	PuzzleTreePrinter ptp(pzl);
	printf("\n%d\n", ptp.print_tree());

#if 0
	PuzzleSolver solver(pzl);
	std::cout << "Solving using " << solver.get_name() << std::endl;
	solver.find_solutions();
	printf("%lu steps, %lu candidates, %lu solutions\n", solver.node_count, solver.validation_count, solver.solutions_found);

	if(solver.find_solutions(1))
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
#endif
}
