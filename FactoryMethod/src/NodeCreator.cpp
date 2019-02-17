#ifndef FACTORYMETHOD_SRC_NODECREATOR_CPP
#define FACTORYMETHOD_SRC_NODECREATOR_CPP

#include "NodeCreator.h"

	NodeCreator::NodeCreator()
	{

	}
	NodeCreator::~NodeCreator()
	{

	}

	Node* createNode()
	{
		Node* new_node;
		new_node = new Node;
		return new_node;
	}

#endif