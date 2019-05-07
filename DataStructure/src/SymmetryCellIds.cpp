#ifndef DATASTRUCTURE_SRC_SYMMETRYCELLIDS_CPP
#define DATASTRUCTURE_SRC_SYMMETRYCELLIDS_CPP

#include "SymmetryCellIds.h"

#include <iostream>
using namespace std;

void SymmetryCellIds::updateBoundary()
{
	return;
	// Symmetry  !!!ATTENTION!!! VÉRIFIER SENS DES NORMALES
	//cout<<"Symmetry cells updating \n";
	Block* block=owner_block_;

	int nb_symmetry_faces=n_cell_in_boundary_;
	//block->n_symmetry_faces_;
	//cout<<"Nb symmetry faces: "<<nb_symmetry_faces<<endl;

	int symmetry_face_idx;

	for(int i=0;i<nb_symmetry_faces;i++)
	{
		
		symmetry_face_idx=block -> block_cells_[cell_ids_in_boundary_[i]]->cell_2_faces_connectivity_[0];
		//block -> block_symmetry_face_ids_[i];
		//cout<<"Face numéro: "<<i<<" Id: "<<symmetry_face_idx<<endl;

		int int_cell_idx=block->block_cells_[cell_ids_in_boundary_[i]]->cell_2_cells_connectivity_[0];
		//block->block_faces_[symmetry_face_idx]->face_2_cells_connectivity_[0];
		int ext_cell_idx=cell_ids_in_boundary_[i];
		//block->block_faces_[symmetry_face_idx]->face_2_cells_connectivity_[1];

		double normalized_x=block->block_faces_[symmetry_face_idx]->face_normals_[0];
		double normalized_y=block->block_faces_[symmetry_face_idx]->face_normals_[1];
		double normalized_z=block->block_faces_[symmetry_face_idx]->face_normals_[2];
		double face_area=block->block_faces_[symmetry_face_idx]->face_area_;



		normalized_x/=face_area;
		normalized_y/=face_area;
		normalized_z/=face_area;

		//cout<<"nx: "<<normalized_x<<" ny: "<<normalized_y<<" nz: "<<normalized_z<<" ss: "<<face_area<<endl;

		double ro_int=block->block_primitive_variables_->ro_[int_cell_idx];
		double uu_int=block->block_primitive_variables_->uu_[int_cell_idx];
		double vv_int=block->block_primitive_variables_->vv_[int_cell_idx];
		double ww_int=block->block_primitive_variables_->ww_[int_cell_idx];
		double pp_int=block->block_primitive_variables_->pp_[int_cell_idx];

		double un1=uu_int*normalized_x+vv_int*normalized_y+ww_int*normalized_z;
		double uu_bc=uu_int-un1*normalized_x;
		double vv_bc=vv_int-un1*normalized_y;
		double ww_bc=ww_int-un1*normalized_z;

		block->block_primitive_variables_->ro_[ext_cell_idx]=ro_int;
		block->block_primitive_variables_->uu_[ext_cell_idx]=2.0*uu_bc-uu_int;
		block->block_primitive_variables_->vv_[ext_cell_idx]=2.0*vv_bc-vv_int;
		block->block_primitive_variables_->ww_[ext_cell_idx]=2.0*ww_bc-ww_int;
		block->block_primitive_variables_->pp_[ext_cell_idx]=pp_int;

		//cout<<"Int cell Id: "<<int_cell_idx<<" uu_int: "<<uu_int<<" nx: "<<normalized_x<<endl;
		//cout<<"Ext cell Id: "<<ext_cell_idx<<" uu_ext: "<<2.0*uu_bc-uu_int<<" uu_bc: "<<uu_bc<<endl;
	}

	// for( int symmetry_cells_idx=0;symmetry_cells_idx<n_cell_in_boundary_;symmetry_cells_idx++)
	// {
	// 	int symmetry_face_idx= (block->block_cells_[symmetry_cells_idx])->cell_2_faces_connectivity_[0];
	// 	int int_cell_idx=block->block_faces_[symmetry_face_idx]->face_2_cells_connectivity_[0];
	// 	int ext_cell_idx=block->block_faces_[symmetry_face_idx]->face_2_cells_connectivity_[1];

	// 	double normalized_x=block->block_faces_[symmetry_face_idx]->face_normals_[0];
	// 	double normalized_y=block->block_faces_[symmetry_face_idx]->face_normals_[1];
	// 	double normalized_z=block->block_faces_[symmetry_face_idx]->face_normals_[2];

	// 	double ro_int=block->block_primitive_variables_->ro_[int_cell_idx];
	// 	double uu_int=block->block_primitive_variables_->uu_[int_cell_idx];
	// 	double vv_int=block->block_primitive_variables_->vv_[int_cell_idx];
	// 	double ww_int=block->block_primitive_variables_->ww_[int_cell_idx];
	// 	double pp_int=block->block_primitive_variables_->pp_[int_cell_idx];

	// 	double un1=uu_int*normalized_x+vv_int*normalized_y+ww_int*normalized_z;// s'assurer du bon sens de la normale!
	// 	double uu_bc=uu_int-un1*normalized_x;
	// 	double vv_bc=vv_int-un1*normalized_y;
	// 	double ww_bc=ww_int-un1*normalized_z;

	// 	block->block_primitive_variables_->ro_[ext_cell_idx]=ro_int;
	// 	block->block_primitive_variables_->uu_[ext_cell_idx]=2.0*uu_bc-uu_int;
	// 	block->block_primitive_variables_->vv_[ext_cell_idx]=2.0*vv_bc-vv_int;
	// 	block->block_primitive_variables_->ww_[ext_cell_idx]=2.0*ww_bc-ww_int;
	// 	block->block_primitive_variables_->pp_[ext_cell_idx]=pp_int;

	// }
	//cout<<"Symmetry cells updated \n";
}
	
SymmetryCellIds::SymmetryCellIds()
{

}

SymmetryCellIds::~SymmetryCellIds()
{

}

#endif
