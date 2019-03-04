#include "BoundaryCellIds_dummy.h"

BoundaryCellIds_dummy::BoundaryCellIds_dummy(int* cell_ids_in_boundary, int n_cell_in_boundary) 
    : n_cell_in_boundary_(n_cell_in_boundary), cell_count_(0), cell_ids_in_boundary_(nullptr) {
    cell_ids_in_boundary_ = new int[n_cell_in_boundary_];
    for (int i = 0; i < n_cell_in_boundary_; i++){
        cell_ids_in_boundary_[i] = cell_ids_in_boundary[i];
    }
}

BoundaryCellIds_dummy::~BoundaryCellIds_dummy(){
    if (cell_ids_in_boundary_ != nullptr){
        delete [] cell_ids_in_boundary_;
    }
}

void BoundaryCellIds_dummy::updateBoundary(){

}