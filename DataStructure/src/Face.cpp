#ifndef DATASTRUCTURE_SRC_FACE_CPP
#define DATASTRUCTURE_SRC_FACE_CPP

#include "Face.h"

Face::Face()
{
	face_normals_ = new double[3]();
	face_2_cells_connectivity_ = new int[2]();
	right_cell_r_vector_ = new double[3]();
	left_cell_r_vector_ = new double[3]();
	face_2_nodes_connectivity_=nullptr;
	face_center_ = new double[3]();
}
Face::~Face()
{
	
	delete[] face_2_nodes_connectivity_;
	delete[] face_normals_;
	delete[] face_2_cells_connectivity_;
	delete[] right_cell_r_vector_;
	delete[] left_cell_r_vector_;

}

#endif