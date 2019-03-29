#ifndef DATASTRUCTURE_SRC_CONNEXIONCELLIDS_CPP
#define DATASTRUCTURE_SRC_CONNEXIONCELLIDS_CPP

#include "BoundaryCellIds.h"
#include "ConnexionCellIds.h"

#include <iostream>

void ConnexionCellIds::updateBoundary()
{
	std::cout<<"Connexion cells updated" << std::endl;
}

ConnexionCellIds::ConnexionCellIds()
{

}

ConnexionCellIds::~ConnexionCellIds(){
    if (cell_ids_in_boundary_other_block_ != nullptr){
        delete [] cell_ids_in_boundary_other_block_;
    }
}

#endif