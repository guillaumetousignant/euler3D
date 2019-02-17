#ifndef DATASTRUCTURE_SRC_NODE_CPP
#define DATASTRUCTURE_SRC_NODE_CPP

#include "Node.h"

Node::Node()
{
	node_coordinates_ = new double[3];
}

Node::~Node()
{
	delete [] node_coordinates_;
}

#endif