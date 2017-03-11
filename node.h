#ifndef NODE_H
#define NODE_H

#include <vector>

enum nodetype
{
	invalid,
//	path_entry,
//	path_exit,
//	path_required,
	path_way,			// Stright line between pathnodes
	path_node,		// Corners and bends
//	required_path,
//	blocked_path,
	face,
	square,
//	sun,
//	triangle,
//	eliminator,
//	tetrimino
};

enum nodecolour
{
	nocol,
	white,
	black
};

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

	// Properties (TODO: Accessor functions??
	enum nodetype type;
	enum nodecolour col;
private:
	Node *route;
};

#endif
