#ifndef DATASTRUCTURE_SRC_WALLCELLIDS_CPP
#define DATASTRUCTURE_SRC_WALLCELLIDS_CPP

#include "WallCellIds.h"

#include <iostream>
using namespace std;

void WallCellIds::updateBoundary()
{
	// WALL  !!!ATTENTION!!! VÉRIFIER SENS DES NORMALES
	cout<<"Wall cells updating \n";
	Block* block=owner_block_;
	for( int wall_cells_idx=0;wall_cells_idx<n_cell_in_boundary_;wall_cells_idx++)
	{
		int wall_face_idx= (block->block_cells_[wall_cells_idx])->cell_2_faces_connectivity_[0];
		int int_cell_idx=block->block_faces_[wall_face_idx]->face_2_cells_connectivity_[0];
		int ext_cell_idx=block->block_faces_[wall_face_idx]->face_2_cells_connectivity_[1];

		double normalized_x=block->block_faces_[wall_face_idx]->face_normals_[0];
		double normalized_y=block->block_faces_[wall_face_idx]->face_normals_[1];
		double normalized_z=block->block_faces_[wall_face_idx]->face_normals_[2];

		double ro_int=block->block_primitive_variables_->ro_[int_cell_idx];
		double uu_int=block->block_primitive_variables_->uu_[int_cell_idx];
		double vv_int=block->block_primitive_variables_->vv_[int_cell_idx];
		double ww_int=block->block_primitive_variables_->ww_[int_cell_idx];
		double pp_int=block->block_primitive_variables_->pp_[int_cell_idx];

		double un1=uu_int*normalized_x+vv_int*normalized_y+ww_int*normalized_z;// s'assurer du bon sens de la normale!
		double uu_bc=uu_int-un1*normalized_x;
		double vv_bc=uu_int-un1*normalized_y;
		double ww_bc=uu_int-un1*normalized_z;

		block->block_primitive_variables_->ro_[ext_cell_idx]=ro_int;
		block->block_primitive_variables_->uu_[ext_cell_idx]=2.0*uu_bc-uu_int;
		block->block_primitive_variables_->vv_[ext_cell_idx]=2.0*vv_bc-vv_int;
		block->block_primitive_variables_->ww_[ext_cell_idx]=2.0*ww_bc-ww_int;
		block->block_primitive_variables_->pp_[ext_cell_idx]=pp_int;

	}
	cout<<"Wall cells updated \n";
}
	
WallCellIds::WallCellIds()
{

}

WallCellIds::~WallCellIds()
{

}

#endif