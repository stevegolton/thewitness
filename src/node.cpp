#include <vector>
#include "node.h"

Node::Node()
{
	route = nullptr;
	x = y = 0;
	//col = nocol;
	type = blank;
	id = 0;
	id2 = 0;
	name = '\0';
	//more = normal;
}

Node::~Node()
{
	// Nothing to do
}

void Node::add_path(Node *node)
{
	paths.push_back(node);
}

int Node::path_count()
{
	return (int)paths.size();
}

void Node::set_route(Node *node)
{
	this->route = node;
}

bool Node::is_routed()
{
	return (route == nullptr)? false : true;
}

Node *Node::get_route()
{
	return route;
}
