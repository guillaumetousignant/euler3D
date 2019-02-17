#ifndef DATASTRUCTURE_SRC_CELL_CPP
#define DATASTRUCTURE_SRC_CELL_CPP

#include "Cell.h"

Cell::Cell()
{
	cell_2_faces_connectivity_size_ = 0;
	cell_2_cells_connectivity_size_ = 0;
	cell_2_nodes_connectivity_size_ = 0;

	cell_2_cells_connectivity_ = nullptr;
	cell_2_nodes_connectivity_ = nullptr;
	cell_2_faces_connectivity_ = nullptr;

	cell_coordinates_ = new double[3];
	cell_weights_ = new double[3];
}

Cell::~Cell()
{
	delete [] cell_coordinates_;
	delete [] cell_weights_;
}

#endif