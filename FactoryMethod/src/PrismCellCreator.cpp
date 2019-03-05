#ifndef FACTORYMETHOD_SRC_PRISMCELLCREATOR_CPP
#define FACTORYMETHOD_SRC_PRISMCELLCREATOR_CPP

#include "PrismCellCreator.h"


Cell* PrismCellCreator::createCell()
{
	Cell* new_cell;
	new_cell = new Cell;
	return new_cell;
	
}

#endif

