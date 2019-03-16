#ifndef FACTORYMETHOD_SRC_CELLCREATOR_CPP
#define FACTORYMETHOD_SRC_CELLCREATOR_CPP

#include "CellCreator.h"


CellCreator::CellCreator()
{

}
CellCreator::~CellCreator()
{

}

Cell* CellCreator::createCell()
{
	Cell* new_cell = new Cell;
	return new_cell;
}


#endif