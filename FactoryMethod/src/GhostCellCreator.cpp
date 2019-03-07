#ifndef FACTORYMETHOD_SRC_GHOSTCELLCREATOR_CPP
#define FACTORYMETHOD_SRC_GHOSTCELLCREATOR_CPP

#include "GhostCellCreator.h"


Cell* GhostCellCreator::createCell()
{
	Cell* new_cell;
	new_cell = new Cell;

	// new_cell -> cell_2_cells_connectivity_ = new int[1];
	// new_cell -> cell_2_faces_connectivity_ = new int[1];
	// new_cell -> cell_coordinates_= new double[3];


	return new_cell;

}

#endif

