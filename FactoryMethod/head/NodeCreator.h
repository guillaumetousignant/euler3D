#ifndef FACTORYMETHOD_HEAD_NODECREATOR_H
#define FACTORYMETHOD_HEAD_NODECREATOR_H

#include "Node.h"

class NodeCreator
{
public:
	NodeCreator();
	~NodeCreator();

	Node* createNode();
	
};

#endif