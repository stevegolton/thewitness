#ifndef PUZZLE_SOLVER_H
#define PUZZLE_SOLVER_H

#include <memory>
#include <string>

#include "puzzle.h"
#include "node.h"

class PuzzleSolver
{
public:
	PuzzleSolver(std::shared_ptr<Puzzle> puzzle);
	std::string get_name();
	bool find_solutions(int solutions = 0);
	bool check_for_exit(Node *node);
	unsigned long validation_count;
	unsigned long node_count;
	unsigned long solutions_found;
private:
	int flood_fill(Node *node, unsigned int type_mask, unsigned int type_count, int id);
	bool validate_route(Node *current_node);
	int follow_route(Node *node, int solutions);
	bool find_squares(Node *node, unsigned int type);
	std::shared_ptr<Puzzle> puzzle;
	std::vector<Node*> required;
	std::vector<Node*> squares;
	std::vector<Node*> entrypoints;
	std::vector< std::vector<Node*> > zones;
	int id;
	int id2;
	int m_prev_zone_count;
};

#endif
