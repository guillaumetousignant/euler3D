#ifndef FACTORYMETHOD_SRC_TETRAHEDRALCELLCREATOR_CPP
#define FACTORYMETHOD_SRC_TETRAHEDRALCELLCREATOR_CPP

#include "TetrahedralCellCreator.h"


Cell* TetrahedralCellCreator::createCell()
{
	Cell* new_cell;
	new_cell = new Cell;

	// new_cell -> cell_2_cells_connectivity_ = new int[4];
	// new_cell -> cell_2_faces_connectivity_ = new int[4];
	// new_cell -> cell_2_nodes_connectivity_ = new int[4];
	// new_cell -> cell_coordinates_= new double[3];
	

	return new_cell;

}

#endif

