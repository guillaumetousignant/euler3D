#ifndef DATASTRUCTURE_SRC_CONNEXIONCELLIDS_CPP
#define DATASTRUCTURE_SRC_CONNEXIONCELLIDS_CPP

#include "BoundaryCellIds.h"
#include "ConnexionCellIds.h"

#include <iostream>

void ConnexionCellIds::updateBoundary()
{
	//std::cout<<"Connexion cells updated" << std::endl;
}

ConnexionCellIds::ConnexionCellIds() : cell_ids_in_boundary_other_block_(nullptr), block_origin_(-1), block_destination_(-1)
{

}

ConnexionCellIds::~ConnexionCellIds(){
    if (cell_ids_in_boundary_other_block_ != nullptr){
        delete [] cell_ids_in_boundary_other_block_;
    }
}

#endif