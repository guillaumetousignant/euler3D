#include "ConnexionCellIds_dummy.h"

ConnexionCellIds_dummy::ConnexionCellIds_dummy(int* cell_ids_in_boundary, int n_cell_in_boundary, int* cell_ids_in_boundary_other_block, int block_origin, int block_destination)
    : BoundaryCellIds_dummy(cell_ids_in_boundary, n_cell_in_boundary), cell_ids_in_boundary_other_block_(nullptr), block_origin_(block_origin), block_destination_(block_destination) {
    cell_ids_in_boundary_other_block_ = new int[n_cell_in_boundary_];
    for (int i = 0; i < n_cell_in_boundary_; i++){
        cell_ids_in_boundary_other_block_[i] = cell_ids_in_boundary_other_block[i];
    }
}

ConnexionCellIds_dummy::~ConnexionCellIds_dummy(){
    if (cell_ids_in_boundary_other_block_ != nullptr){
        delete [] cell_ids_in_boundary_other_block_;
    }
}