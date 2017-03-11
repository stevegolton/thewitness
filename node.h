#ifndef NODE_H
#define NODE_H

#include <vector>

enum nodetype
{
	blank,
	path_node,
	path_node_required,
	path_node_entry,
	path_node_exit,
	path_way_vertical,
	path_way_horizontal,
	path_way_required_vertical,
	path_way_required_horizontal,
	path_way_blocked_vertical,
	path_way_blocked_horizontal,
	face,
	face_square_white,
	face_square_black,
	invalid
//	sun,
//	triangle,
//	eliminator,
//	tetrimino
};

/*
enum nodecolour
{
	nocol,
	white,
	black
};

enum nodemisc
{
	normal,
	required,
	blocked,
	node_entry,
	node_exit
};
*/

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
	//enum nodecolour col;
	//enum nodemisc more;
private:
	Node *route;
};

#endif
