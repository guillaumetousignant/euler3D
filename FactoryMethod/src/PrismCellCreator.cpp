#ifndef FACTORYMETHOD_SRC_PRISMCELLCREATOR_CPP
#define FACTORYMETHOD_SRC_PRISMCELLCREATOR_CPP

#include "PrismCellCreator.h"


Cell* PrismCellCreator::createCell()
{
	Cell* new_cell;
	new_cell = new Cell;

	new_cell -> cell_2_cells_connectivity_ = new int[6];
	new_cell -> cell_2_faces_connectivity_ = new int[6];
	new_cell -> cell_2_nodes_connectivity_ = new int[8];
	new_cell -> cell_coordinates_= new double[3];

	return new_cell;
	
}

#endif

