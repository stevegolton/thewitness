#include <vector>
#include "node.h"

Node::Node()
{
	this->route = nullptr;
	this->x = this->y = 0;
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

void Node::set_path(Node *node)
{
	this->route = node;
}

bool Node::is_routed()
{
	return (route == nullptr)? false : true;
}

void Node::set_route(Node *node)
{
	route = node;
}

Node *Node::get_route()
{
	return route;
}
