#ifndef DATASTRUCTURE_SRC_CELL_CPP
#define DATASTRUCTURE_SRC_CELL_CPP

#include "Cell.h"

Cell::Cell()
{
	cell_coordinates_ = new double[3];
	
	cell_weights_ = new double[3]();
}

Cell::~Cell()
{

}

#endif