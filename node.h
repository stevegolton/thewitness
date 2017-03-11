#ifndef NODE_H
#define NODE_H

#include <vector>

class Node
{
public:
	Node();
	~Node();
	void add_path(Node *node);
	int path_count();
	void set_path(Node *node);
	bool is_routed();
	void set_route(Node *node);
	Node *get_route();
	std::vector<Node*> paths;
	int x;
	int y;
private:
	Node *route;
};

#endif
