#ifndef FACTORYMETHOD_HEAD_CELLCREATOR_H
#define FACTORYMETHOD_HEAD_CELLCREATOR_H

#include "Cell.h"

class CellCreator
{
public:
	CellCreator();
	~CellCreator();

	virtual Cell* createNode() = 0;
	
};

#endif