#ifndef FACTORYMETHOD_SRC_CELLCREATOR_CPP
#define FACTORYMETHOD_SRC_CELLCREATOR_CPP

#include "GhostCellCreator.h"


Cell* GhostCellCreator::createCell()
{
	Cell* new_cell;
	new_cell = new Cell;
	return new_cell;

	new_cell -> cell_2_cells_connectivity_ = new int[1];
}

#endif

