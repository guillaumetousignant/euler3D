#ifndef DATASTRUCTURE_SRC_BOUNDARYCELLIDS_CPP
#define DATASTRUCTURE_SRC_BOUNDARYCELLIDS_CPP

#include "BoundaryCellIds.h"
#include <string>
#include <iostream>
using namespace std;

void BoundaryCellIds::updateBoundary()
{

}
	
BoundaryCellIds::BoundaryCellIds() : cell_count_(nullptr), n_cell_in_boundary_(0), cell_ids_in_boundary_(nullptr), owner_block_(nullptr)
{

}

BoundaryCellIds::~BoundaryCellIds()
{
    if (cell_count_ != nullptr){
        delete cell_count_;
    }

    if (cell_ids_in_boundary_ != nullptr){
        delete [] cell_ids_in_boundary_;
    }
}

#endif

