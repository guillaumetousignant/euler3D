#ifndef DATASTRUCTURE_SRC_FACE_CPP
#define DATASTRUCTURE_SRC_FACE_CPP

#include "Face.h"

Face::Face()
{
	face_normals_ = new double[3];
	right_cell_r_vector_ = new double[3];
	left_cell_r_vector_ = new double[3];
	face_center_ = new double[3];
}

Face::~Face()
{

}

#endif