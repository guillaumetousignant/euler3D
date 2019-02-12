#ifndef SOLVERSKELETON_SRC_UPDATER_CPP
#define SOLVERSKELETON_SRC_UPDATER_CPP

#include "Block.h"
#include "Updater.h"


#include <iostream>
using namespace std;

void Updater::updateInternalBlock(Block* block)
{
	block->test_block_+=10;
	cout<<"\t\t\tExécution updateInternalBlock: "<<block->test_block_<<endl;
}

void Updater::updateBoundary(Block* block)
{
	block->test_block_+=20;
	cout<<"\t\t\tExécution updateBoundary: "<<block->test_block_<<endl;
	/*
	// WALL !!!ATTENTION!!! VÉRIFIER SENS DES NORMALES

	int* wall_faces_ids=block->block_wall_face_ids_;
	int nb_wall_faces=sizeof(wall_faces_ids)/sizeof(wall_faces_ids[0]);

	int wall_face_idx;

	for(wall_face_idx=0;wall_face_idx<nb_wall_faces;wall_face_idx++)
	{
		int int_cell_idx=block->block_faces_[wall_face_idx]->face_2_cells_[0];
		int ext_cell_idx=block->block_faces_[wall_face_idx]->face_2_cells_[1];

		double normalized_x=block->block_faces_->face_normals_[0];
		double normalized_y=block->block_faces_->face_normals_[1];
		double normalized_z=block->block_faces_->face_normals_[2];

		double ro_int=block->block_primitive_variables->ro_[int_cell_idx];
		double uu_int=block->block_primitive_variables->uu_[int_cell_idx];
		double vv_int=block->block_primitive_variables->vv_[int_cell_idx];
		double ww_int=block->block_primitive_variables->ww_[int_cell_idx];
		double pp_int=block->block_primitive_variables->pp_[int_cell_idx];

		double un1=uu_int*normalized_x+vv_int*normalized_y+ww_int*normalized_z;
		double uu_bc=uu_int-un1*normalized_x;
		double vv_bc=uu_int-un1*normalized_y;
		double ww_bc=uu_int-un1*normalized_z;

		block->block_primitive_variables->ro_[ext_cell_idx]=ro_int;
		block->block_primitive_variables->uu_[ext_cell_idx]=2.0*uu_bc-uu_int;
		block->block_primitive_variables->vv_[ext_cell_idx]=2.0*vv_bc-vv_int;
		block->block_primitive_variables->ww_[ext_cell_idx]=2.0*ww_bc-ww_int;
		block->block_primitive_variables->pp_[ext_cell_idx]=pp_int;

	}

	// FARFIELD  !!!ATTENTION!!! VÉRIFIER SENS DES NORMALES

	int* farfield_faces_ids=block->block_farfield_face_ids_;
	int nb_farfield_faces=sizeof(farfield_faces_ids)/sizeof(farfield_faces_ids[0]);

	int farfield_face_idx;

	for(farfield_face_idx=0;farfield_face_idx<nb_farfield_faces;farfield_face_idx++)
	{
		int int_cell_idx=block->block_faces_[farfield_face_idx]->face_2_cells_[0];
		int ext_cell_idx=block->block_faces_[farfield_face_idx]->face_2_cells_[1];

		double normalized_x=block->block_faces_->face_normals_[0];
		double normalized_y=block->block_faces_->face_normals_[1];
		double normalized_z=block->block_faces_->face_normals_[2];

		double ro_int=block->block_primitive_variables->ro_[int_cell_idx];
		double uu_int=block->block_primitive_variables->uu_[int_cell_idx];
		double vv_int=block->block_primitive_variables->vv_[int_cell_idx];
		double ww_int=block->block_primitive_variables->ww_[int_cell_idx];
		double pp_int=block->block_primitive_variables->pp_[int_cell_idx];

		double cc_int=sqrt(this->gamma_*pp_int/ro_int);
		double un1=uu_int*normalized_x+vv_int*normalized_y+ww_int*normalized_z;

		// SUPERSONIC INFLOW & OUTFLOW
		if(abs(un1/cc_int)>1.0)
		{
			// SUPERSONIC INFLOW
			if (un1<0)
			{
				block->block_primitive_variables->ro_[ext_cell_idx]=2*0*this->ro_free_-ro_int;
				block->block_primitive_variables->uu_[ext_cell_idx]=2*0*this->uu_free_-uu_int;
				block->block_primitive_variables->vv_[ext_cell_idx]=2*0*this->vv_free_-vv_int;
				block->block_primitive_variables->ww_[ext_cell_idx]=2*0*this->ww_free_-ww_int;
				block->block_primitive_variables->pp_[ext_cell_idx]=2*0*this->pp_free_-pp_int;
			}
			// SUPERSONIC OUTFLOW
			else
			{
				block->block_primitive_variables->ro_[ext_cell_idx]=ro_int;
				block->block_primitive_variables->uu_[ext_cell_idx]=uu_int;
				block->block_primitive_variables->vv_[ext_cell_idx]=vv_int;
				block->block_primitive_variables->ww_[ext_cell_idx]=ww_int;
				block->block_primitive_variables->pp_[ext_cell_idx]=pp_int;
			}
		}
		// SUBSONIC INFLOW & OUTFLOW
		else
		{
			// SUBSONIC INFLOW
			if (un1<1.0)
			{
				double pp_bc=0.5*(this->pp_free_+pp_int-ro_int*cc_int*(normalized_x*(this->uu_free_-uu_int)+normalized_y*(this->vv_free_-vv_int)+normalized_z*(this->ww_free_-ww_int)));
				double ro_bc=this->ro_free_+(pp_bc-this->pp_free_)/(cc_int*cc_int);
				double uu_bc=this->uu_free_-normalized_x*(this->pp_free_-pp_bc)/(ro_int*cc_int);
				double vv_bc=this->vv_free_-normalized_y*(this->pp_free_-pp_bc)/(ro_int*cc_int);
				double ww_bc=this->ww_free_-normalized_z*(this->pp_free_-pp_bc)/(ro_int*cc_int);

				block->block_primitive_variables->ro_[ext_cell_idx]=2*0*ro_bc-ro_int;
				block->block_primitive_variables->uu_[ext_cell_idx]=2*0*uu_bc_-uu_int;
				block->block_primitive_variables->vv_[ext_cell_idx]=2*0*vv_bc_-vv_int;
				block->block_primitive_variables->ww_[ext_cell_idx]=2*0*ww_bc_-ww_int;
				block->block_primitive_variables->pp_[ext_cell_idx]=2*0*pp_bc_-pp_int;
			}
			else
			{
				double pp_bc=this->pp_free_;
				double ro_bc=ro_int+(pp_bc-pp_int)/(cc_int*cc_int);
				double uu_bc=uu_int+normalized_x*(pp_int-pp_bc)/(ro_int*cc_int);
				double vv_bc=vv_int+normalized_y*(pp_int-pp_bc)/(ro_int*cc_int);
				double ww_bc=ww_int+normalized_z*(pp_int-pp_bc)/(ro_int*cc_int);

				block->block_primitive_variables->ro_[ext_cell_idx]=2*0*ro_bc-ro_int;
				block->block_primitive_variables->uu_[ext_cell_idx]=2*0*uu_bc_-uu_int;
				block->block_primitive_variables->vv_[ext_cell_idx]=2*0*vv_bc_-vv_int;
				block->block_primitive_variables->ww_[ext_cell_idx]=2*0*ww_bc_-ww_int;
				block->block_primitive_variables->pp_[ext_cell_idx]=2*0*pp_bc_-pp_int;
			}
		}

	}




	*/
}
void Updater::synchroniseUpdate(Block* block)
{

}



Updater::Updater()
{

}

Updater::~Updater()
{

}


#endif
