#ifndef DATASTRUCTURE_SRC_FARFIELDCELLIDS_CPP
#define DATASTRUCTURE_SRC_FARFIELDCELLIDS_CPP

#include "FarfieldCellIds.h"

#include <iostream>
#include <cmath>
using namespace std;

void FarfieldCellIds::updateBoundary()
{
	cout<<"Farfield cells updating \n";

	// FARFIELD  !!!ATTENTION!!! VÉRIFIER SENS DES NORMALES
	Block* block=owner_block_;
	//int* farfield_faces_ids=block->block_farfield_face_ids_;
	//int nb_farfield_faces=sizeof(farfield_faces_ids)/sizeof(farfield_faces_ids[0]);

	//int farfield_face_idx;

	for(int farfield_cells_idx=0;farfield_cells_idx<n_cell_in_boundary_;farfield_cells_idx++)
	{
		int farfield_face_idx= (block->block_cells_[farfield_cells_idx])->cell_2_faces_connectivity_[0];
		//std::cout<<"boucle update face: "<<farfield_face_idx<<std::endl;
		int int_cell_idx=block->block_faces_[farfield_face_idx]->face_2_cells_connectivity_[0];
		//std::cout<<"boucle update int cell: "<<int_cell_idx<<std::endl;
		int ext_cell_idx=block->block_faces_[farfield_face_idx]->face_2_cells_connectivity_[1];
		//std::cout<<"boucle update ext cell: "<<ext_cell_idx<<std::endl;

		double normalized_x=block->block_faces_[farfield_face_idx]->face_normals_[0];
		double normalized_y=block->block_faces_[farfield_face_idx]->face_normals_[1];
		double normalized_z=block->block_faces_[farfield_face_idx]->face_normals_[2];

		double ro_int=block->block_primitive_variables_->ro_[int_cell_idx];
		double uu_int=block->block_primitive_variables_->uu_[int_cell_idx];
		double vv_int=block->block_primitive_variables_->vv_[int_cell_idx];
		double ww_int=block->block_primitive_variables_->ww_[int_cell_idx];
		double pp_int=block->block_primitive_variables_->pp_[int_cell_idx];

		double cc_int=sqrt((block->block_primitive_variables_->gamma_)*(pp_int)/ro_int);
		double un1=uu_int*normalized_x+vv_int*normalized_y+ww_int*normalized_z;

		// SUPERSONIC INFLOW & OUTFLOW
		if(fabs(un1/cc_int)>1.0)
		{
			// SUPERSONIC INFLOW
			if (un1<0)
			{
				block->block_primitive_variables_->ro_[ext_cell_idx]=2.0*((block->block_primitive_variables_)->ro_free_)-ro_int;
				block->block_primitive_variables_->uu_[ext_cell_idx]=2.0*((block->block_primitive_variables_)->uu_free_)-uu_int;
				block->block_primitive_variables_->vv_[ext_cell_idx]=2.0*((block->block_primitive_variables_)->vv_free_)-vv_int;
				block->block_primitive_variables_->ww_[ext_cell_idx]=2.0*((block->block_primitive_variables_)->ww_free_)-ww_int;
				block->block_primitive_variables_->pp_[ext_cell_idx]=2.0*((block->block_primitive_variables_)->pp_free_)-pp_int;
			}
			// SUPERSONIC OUTFLOW
			else
			{
				block->block_primitive_variables_->ro_[ext_cell_idx]=ro_int;
				block->block_primitive_variables_->uu_[ext_cell_idx]=uu_int;
				block->block_primitive_variables_->vv_[ext_cell_idx]=vv_int;
				block->block_primitive_variables_->ww_[ext_cell_idx]=ww_int;
				block->block_primitive_variables_->pp_[ext_cell_idx]=pp_int;
			}
		}
		// SUBSONIC INFLOW & OUTFLOW
		else
		{
			// SUBSONIC INFLOW
			if (un1<1.0)
			{
				double pp_bc=0.5*(((block->block_primitive_variables_)->pp_free_)+pp_int-ro_int*cc_int*(normalized_x*(((block->block_primitive_variables_)->uu_free_)-uu_int)+normalized_y*(((block->block_primitive_variables_)->vv_free_)-vv_int)+normalized_z*(((block->block_primitive_variables_)->ww_free_)-ww_int)));
				double ro_bc=((block->block_primitive_variables_)->ro_free_)+(pp_bc-((block->block_primitive_variables_)->pp_free_))/(cc_int*cc_int);
				double uu_bc=((block->block_primitive_variables_)->uu_free_)-normalized_x*(((block->block_primitive_variables_)->pp_free_)-pp_bc)/(ro_int*cc_int);
				double vv_bc=((block->block_primitive_variables_)->vv_free_)-normalized_y*(((block->block_primitive_variables_)->pp_free_)-pp_bc)/(ro_int*cc_int);
				double ww_bc=((block->block_primitive_variables_)->ww_free_)-normalized_z*(((block->block_primitive_variables_)->pp_free_)-pp_bc)/(ro_int*cc_int);

				block->block_primitive_variables_->ro_[ext_cell_idx]=2.0*ro_bc-ro_int;
				block->block_primitive_variables_->uu_[ext_cell_idx]=2.0*uu_bc-uu_int;
				block->block_primitive_variables_->vv_[ext_cell_idx]=2.0*vv_bc-vv_int;
				block->block_primitive_variables_->ww_[ext_cell_idx]=2.0*ww_bc-ww_int;
				block->block_primitive_variables_->pp_[ext_cell_idx]=2.0*pp_bc-pp_int;
			}
			else
			{
				double pp_bc=((block->block_primitive_variables_)->pp_free_);
				double ro_bc=ro_int+(pp_bc-pp_int)/(cc_int*cc_int);
				double uu_bc=uu_int+normalized_x*(pp_int-pp_bc)/(ro_int*cc_int);
				double vv_bc=vv_int+normalized_y*(pp_int-pp_bc)/(ro_int*cc_int);
				double ww_bc=ww_int+normalized_z*(pp_int-pp_bc)/(ro_int*cc_int);

				block->block_primitive_variables_->ro_[ext_cell_idx]=2.0*ro_bc-ro_int;
				block->block_primitive_variables_->uu_[ext_cell_idx]=2.0*uu_bc-uu_int;
				block->block_primitive_variables_->vv_[ext_cell_idx]=2.0*vv_bc-vv_int;
				block->block_primitive_variables_->ww_[ext_cell_idx]=2.0*ww_bc-ww_int;
				block->block_primitive_variables_->pp_[ext_cell_idx]=2.0*pp_bc-pp_int;
			}
		}

	}

	cout<<"Farfield cells updated \n";
}
	
FarfieldCellIds::FarfieldCellIds()
{

}

FarfieldCellIds::~FarfieldCellIds()
{

}

#endif