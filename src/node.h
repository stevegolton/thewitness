#ifndef NODE_H
#define NODE_H

#include <vector>

const unsigned int blank						= 1ULL <<  0;
const unsigned int path_node					= 1ULL <<  1;
const unsigned int path_node_required			= 1ULL <<  2;
const unsigned int path_node_entry				= 1ULL <<  3;
const unsigned int path_node_exit				= 1ULL <<  4;
const unsigned int path_way_vertical			= 1ULL <<  5;
const unsigned int path_way_horizontal			= 1ULL <<  6;
const unsigned int path_way_required_vertical	= 1ULL <<  7;
const unsigned int path_way_required_horizontal	= 1ULL <<  8;
const unsigned int path_way_blocked_vertical	= 1ULL <<  9;
const unsigned int path_way_blocked_horizontal	= 1ULL << 10;
const unsigned int face							= 1ULL << 11;
const unsigned int face_square_white			= 1ULL << 12;
const unsigned int face_square_black			= 1ULL << 13;
const unsigned int invalid						= 1ULL << 14;

class Node
{
public:
	Node();
	~Node();
	void add_path(Node *node);
	int path_count();

	void set_route(Node *node);
	bool is_routed();
	Node *get_route();

	std::vector<Node*> paths;
	int x;
	int y;
	int id;
	int id2;
	unsigned int type;
	char name;
private:
	Node *route;
};

#endif
