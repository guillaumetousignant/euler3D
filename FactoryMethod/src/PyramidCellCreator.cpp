#ifndef FACTORYMETHOD_SRC_PYRAMIDCELLCREATOR_CPP
#define FACTORYMETHOD_SRC_PYRAMIDCELLCREATOR_CPP

#include "PyramidCellCreator.h"


Cell* PyramidCellCreator::createCell()
{
	Cell* new_cell;
	new_cell = new Cell;

	new_cell -> cell_2_cells_connectivity_ = new int[5];
	new_cell -> cell_2_faces_connectivity_ = new int[5];
	new_cell -> cell_2_nodes_connectivity_ = new int[5];
	new_cell -> cell_coordinates_= new double[3];
	

	return new_cell;

}

#endif

