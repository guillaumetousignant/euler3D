#ifndef SOLVERSKELETON_SRC_UPDATER_CPP
#define SOLVERSKELETON_SRC_UPDATER_CPP

#include "Block.h"
#include "Updater.h"


#include <iostream>
#include <math.h>
using namespace std;

void Updater::updateInternalBlock(Block* block)
{
	//cout<<"\t\t\tExécution updateInternalBlock: "<<endl;

	int nb_cells=block->n_real_cells_in_block_; // real cells or all cells ?????????
	int cell_idx;
	double ro_0,ru_0,rv_0,rw_0,re_0;
	double dt;
	double cell_volume;
	double res_ro_conv,res_uu_conv,res_vv_conv,res_ww_conv,res_pp_conv;
	double res_ro_diss,res_uu_diss,res_vv_diss,res_ww_diss,res_pp_diss;

	double ro_new,ru_new,rv_new,rw_new,re_new;
	double ro, uu, vv, ww, pp;

	PrimitiveVariables* my_primitive_variables;
	my_primitive_variables = block -> block_primitive_variables_;


	for (cell_idx=0;cell_idx<nb_cells;cell_idx++)
	{
		ro_0= my_primitive_variables->ro_0_[cell_idx];
		ru_0= my_primitive_variables->ru_0_[cell_idx];
		rv_0= my_primitive_variables->rv_0_[cell_idx];
		rw_0= my_primitive_variables->rw_0_[cell_idx];
		re_0= my_primitive_variables->re_0_[cell_idx];

		dt=block->block_time_variables_->dt_[cell_idx];
		cell_volume=block->block_cells_[cell_idx]->cell_volume_;

		res_ro_conv = my_primitive_variables->conv_res_ro_[cell_idx];
		res_uu_conv = my_primitive_variables->conv_res_uu_[cell_idx];
		res_vv_conv = my_primitive_variables->conv_res_vv_[cell_idx];
		res_ww_conv = my_primitive_variables->conv_res_ww_[cell_idx];
		res_pp_conv = my_primitive_variables->conv_res_pp_[cell_idx];

		res_ro_diss = my_primitive_variables->diss_res_ro_[cell_idx];
		res_uu_diss = my_primitive_variables->diss_res_uu_[cell_idx];
		res_vv_diss = my_primitive_variables->diss_res_vv_[cell_idx];
		res_ww_diss = my_primitive_variables->diss_res_ww_[cell_idx];
		res_pp_diss = my_primitive_variables->diss_res_pp_[cell_idx];

		ro_new=ro_0-(alpha_rk_[current_stage_]*dt/cell_volume)*(res_ro_conv-res_ro_diss);
		ru_new=ru_0-(alpha_rk_[current_stage_]*dt/cell_volume)*(res_uu_conv-res_uu_diss);
		rv_new=rv_0-(alpha_rk_[current_stage_]*dt/cell_volume)*(res_vv_conv-res_vv_diss);
		rw_new=rw_0-(alpha_rk_[current_stage_]*dt/cell_volume)*(res_ww_conv-res_ww_diss);
		re_new=re_0-(alpha_rk_[current_stage_]*dt/cell_volume)*(res_pp_conv-res_pp_diss);

		ro=ro_new;
		uu= ru_new/ro_new;
		vv= rv_new/ro_new;
		ww= rw_new/ro_new;
		pp=(gamma_-1.0)*(re_new-0.5*(ru_new*ru_new+rv_new*rv_new+rw_new*rw_new)/ro_new);

		//cout<<"block_id: "<< block->block_id_<<" cell_idx: "<<cell_idx<<" ro_0: "<<ro_0<<" ro_new: "<<ro_new<<endl;
		//cout<<"dt: "<<dt<<" cell_volume: "<<cell_volume<<" res_ro_conv-res_ro_diss: "<<res_ro_conv-res_ro_diss<<" alpha_rk_[current_stage_]: "<<alpha_rk_[current_stage_]<<endl;
		//cout<<"cell_idx: "<<cell_idx<<" ri_1: "<<(res_ro_conv-res_ro_diss)<<" ri_2: "<<(res_uu_conv-res_uu_diss)<<" ri_3: "<<(res_vv_conv-res_vv_diss)<<" ri_5: "<<(res_pp_conv-res_pp_diss)<<endl;

		my_primitive_variables->ro_[cell_idx]=ro;
		my_primitive_variables->uu_[cell_idx]=uu;
		my_primitive_variables->vv_[cell_idx]=vv;
		my_primitive_variables->ww_[cell_idx]=ww;
		my_primitive_variables->pp_[cell_idx]=pp;

	}

}

void Updater::updateBoundary(Block* block)
{
	//cout<<"\t\t\tExécution updateBoundary: "<<endl;

	for(int i=0;i<block->n_real_boundaries_in_block_;i++)
	{
		block->block_boundary_cell_ids_[i]->updateBoundary();
	}



	// int nb_wall_faces=block->n_wall_faces_;
	// //cout<<"Nb wall faces: "<<nb_wall_faces<<endl;

	// int i;
	// int wall_face_idx;

	// for(i=0;i<nb_wall_faces;i++)
	// {
	// 	wall_face_idx=block -> block_wall_face_ids_[i];
	// 	//cout<<"Face numéro: "<<i<<" Id: "<<wall_face_idx<<endl;

	// 	int int_cell_idx=block->block_faces_[wall_face_idx]->face_2_cells_connectivity_[0];
	// 	int ext_cell_idx=block->block_faces_[wall_face_idx]->face_2_cells_connectivity_[1];

	// 	double normalized_x=block->block_faces_[wall_face_idx]->face_normals_[0];
	// 	double normalized_y=block->block_faces_[wall_face_idx]->face_normals_[1];
	// 	double normalized_z=block->block_faces_[wall_face_idx]->face_normals_[2];
	// 	double face_area=block->block_faces_[wall_face_idx]->face_area_;



	// 	normalized_x/=face_area;
	// 	normalized_y/=face_area;
	// 	normalized_z/=face_area;

	// 	//cout<<"nx: "<<normalized_x<<" ny: "<<normalized_y<<" nz: "<<normalized_z<<" ss: "<<face_area<<endl;

	// 	double ro_int=block->block_primitive_variables_->ro_[int_cell_idx];
	// 	double uu_int=block->block_primitive_variables_->uu_[int_cell_idx];
	// 	double vv_int=block->block_primitive_variables_->vv_[int_cell_idx];
	// 	double ww_int=block->block_primitive_variables_->ww_[int_cell_idx];
	// 	double pp_int=block->block_primitive_variables_->pp_[int_cell_idx];

	// 	double un1=uu_int*normalized_x+vv_int*normalized_y+ww_int*normalized_z;
	// 	double uu_bc=uu_int-un1*normalized_x;
	// 	double vv_bc=vv_int-un1*normalized_y;
	// 	double ww_bc=ww_int-un1*normalized_z;

	// 	block->block_primitive_variables_->ro_[ext_cell_idx]=ro_int;
	// 	block->block_primitive_variables_->uu_[ext_cell_idx]=2.0*uu_bc-uu_int;
	// 	block->block_primitive_variables_->vv_[ext_cell_idx]=2.0*vv_bc-vv_int;
	// 	block->block_primitive_variables_->ww_[ext_cell_idx]=2.0*ww_bc-ww_int;
	// 	block->block_primitive_variables_->pp_[ext_cell_idx]=pp_int;

	// 	//cout<<"Int cell Id: "<<int_cell_idx<<" uu_int: "<<uu_int<<" nx: "<<normalized_x<<endl;
	// 	//cout<<"Ext cell Id: "<<ext_cell_idx<<" uu_ext: "<<2.0*uu_bc-uu_int<<" uu_bc: "<<uu_bc<<endl;
	// }

	// int nb_symmetry_faces=block->n_symmetry_faces_;
	// //cout<<"Nb symmetry faces: "<<nb_symmetry_faces<<endl;

	// int symmetry_face_idx;

	// for(i=0;i<nb_symmetry_faces;i++)
	// {
	// 	symmetry_face_idx=block -> block_symmetry_face_ids_[i];
	// 	//cout<<"Face numéro: "<<i<<" Id: "<<symmetry_face_idx<<endl;

	// 	int int_cell_idx=block->block_faces_[symmetry_face_idx]->face_2_cells_connectivity_[0];
	// 	int ext_cell_idx=block->block_faces_[symmetry_face_idx]->face_2_cells_connectivity_[1];

	// 	double normalized_x=block->block_faces_[symmetry_face_idx]->face_normals_[0];
	// 	double normalized_y=block->block_faces_[symmetry_face_idx]->face_normals_[1];
	// 	double normalized_z=block->block_faces_[symmetry_face_idx]->face_normals_[2];
	// 	double face_area=block->block_faces_[symmetry_face_idx]->face_area_;



	// 	normalized_x/=face_area;
	// 	normalized_y/=face_area;
	// 	normalized_z/=face_area;

	// 	//cout<<"nx: "<<normalized_x<<" ny: "<<normalized_y<<" nz: "<<normalized_z<<" ss: "<<face_area<<endl;

	// 	double ro_int=block->block_primitive_variables_->ro_[int_cell_idx];
	// 	double uu_int=block->block_primitive_variables_->uu_[int_cell_idx];
	// 	double vv_int=block->block_primitive_variables_->vv_[int_cell_idx];
	// 	double ww_int=block->block_primitive_variables_->ww_[int_cell_idx];
	// 	double pp_int=block->block_primitive_variables_->pp_[int_cell_idx];

	// 	double un1=uu_int*normalized_x+vv_int*normalized_y+ww_int*normalized_z;
	// 	double uu_bc=uu_int-un1*normalized_x;
	// 	double vv_bc=vv_int-un1*normalized_y;
	// 	double ww_bc=ww_int-un1*normalized_z;

	// 	block->block_primitive_variables_->ro_[ext_cell_idx]=ro_int;
	// 	block->block_primitive_variables_->uu_[ext_cell_idx]=2.0*uu_bc-uu_int;
	// 	block->block_primitive_variables_->vv_[ext_cell_idx]=2.0*vv_bc-vv_int;
	// 	block->block_primitive_variables_->ww_[ext_cell_idx]=2.0*ww_bc-ww_int;
	// 	block->block_primitive_variables_->pp_[ext_cell_idx]=pp_int;

	// 	//cout<<"Int cell Id: "<<int_cell_idx<<" uu_int: "<<uu_int<<" nx: "<<normalized_x<<endl;
	// 	//cout<<"Ext cell Id: "<<ext_cell_idx<<" uu_ext: "<<2.0*uu_bc-uu_int<<" uu_bc: "<<uu_bc<<endl;
	// }

	// int nb_farfield_faces=block->n_farfield_faces_;
	// //cout<<"Nb farfield faces: "<<nb_farfield_faces<<endl;

	// // FARFIELD  !!!ATTENTION!!! VÉRIFIER SENS DES NORMALES
	// int farfield_face_idx;

	// double ro_free=block->block_primitive_variables_->ro_free_;
	// double uu_free=block->block_primitive_variables_->uu_free_;
	// double vv_free=block->block_primitive_variables_->vv_free_;
	// double ww_free=block->block_primitive_variables_->ww_free_;
	// double pp_free=block->block_primitive_variables_->pp_free_;

	// for(i=0;i<nb_farfield_faces;i++)
	// {
	// 	farfield_face_idx=block -> block_farfield_face_ids_[i];
	// 	//cout<<"Face numéro: "<<i<<" Id: "<<farfield_face_idx<<endl;

	// 	int int_cell_idx=block->block_faces_[farfield_face_idx]->face_2_cells_connectivity_[0];
	// 	int ext_cell_idx=block->block_faces_[farfield_face_idx]->face_2_cells_connectivity_[1];

	// 	double normalized_x=block->block_faces_[farfield_face_idx]->face_normals_[0];
	// 	double normalized_y=block->block_faces_[farfield_face_idx]->face_normals_[1];
	// 	double normalized_z=block->block_faces_[farfield_face_idx]->face_normals_[2];
	// 	double face_area=block->block_faces_[farfield_face_idx]->face_area_;

	// 	normalized_x/=face_area;
	// 	normalized_y/=face_area;
	// 	normalized_z/=face_area;

	// 	double ro_int=block->block_primitive_variables_->ro_[int_cell_idx];
	// 	double uu_int=block->block_primitive_variables_->uu_[int_cell_idx];
	// 	double vv_int=block->block_primitive_variables_->vv_[int_cell_idx];
	// 	double ww_int=block->block_primitive_variables_->ww_[int_cell_idx];
	// 	double pp_int=block->block_primitive_variables_->pp_[int_cell_idx];



	// 	double cc_int=sqrt(this->gamma_*pp_int/ro_int);
	// 	double un1=uu_int*normalized_x+vv_int*normalized_y+ww_int*normalized_z;

	// 	// SUPERSONIC INFLOW & OUTFLOW
	// 	if(fabs(un1/cc_int)>1.0)
	// 	{
	// 		// SUPERSONIC INFLOW
	// 		if (un1<0.0)
	// 		{
	// 			block->block_primitive_variables_->ro_[ext_cell_idx]=2.0*ro_free-ro_int;
	// 			block->block_primitive_variables_->uu_[ext_cell_idx]=2.0*uu_free-uu_int;
	// 			block->block_primitive_variables_->vv_[ext_cell_idx]=2.0*vv_free-vv_int;
	// 			block->block_primitive_variables_->ww_[ext_cell_idx]=2.0*ww_free-ww_int;
	// 			block->block_primitive_variables_->pp_[ext_cell_idx]=2.0*pp_free-pp_int;
	// 		}
	// 		// SUPERSONIC OUTFLOW
	// 		else
	// 		{
	// 			block->block_primitive_variables_->ro_[ext_cell_idx]=ro_int;
	// 			block->block_primitive_variables_->uu_[ext_cell_idx]=uu_int;
	// 			block->block_primitive_variables_->vv_[ext_cell_idx]=vv_int;
	// 			block->block_primitive_variables_->ww_[ext_cell_idx]=ww_int;
	// 			block->block_primitive_variables_->pp_[ext_cell_idx]=pp_int;
	// 		}
	// 	}
	// 	// SUBSONIC INFLOW & OUTFLOW
	// 	else
	// 	{
	// 		// SUBSONIC INFLOW
	// 		if (un1<0.0)
	// 		{
	// 			double pp_bc=0.5*(pp_free+pp_int-ro_int*cc_int*(normalized_x*(uu_free-uu_int)+normalized_y*(vv_free-vv_int)+normalized_z*(ww_free-ww_int)));
	// 			double ro_bc=ro_free+(pp_bc-pp_free)/(cc_int*cc_int);
	// 			double uu_bc=uu_free-normalized_x*(pp_free-pp_bc)/(ro_int*cc_int);
	// 			double vv_bc=vv_free-normalized_y*(pp_free-pp_bc)/(ro_int*cc_int);
	// 			double ww_bc=ww_free-normalized_z*(pp_free-pp_bc)/(ro_int*cc_int);

	// 			block->block_primitive_variables_->ro_[ext_cell_idx]=2.0*ro_bc-ro_int;
	// 			block->block_primitive_variables_->uu_[ext_cell_idx]=2.0*uu_bc-uu_int;
	// 			block->block_primitive_variables_->vv_[ext_cell_idx]=2.0*vv_bc-vv_int;
	// 			block->block_primitive_variables_->ww_[ext_cell_idx]=2.0*ww_bc-ww_int;
	// 			block->block_primitive_variables_->pp_[ext_cell_idx]=2.0*pp_bc-pp_int;
	// 		}
	// 		else
	// 		{
	// 			double pp_bc=pp_free;
	// 			double ro_bc=ro_int+(pp_bc-pp_int)/(cc_int*cc_int);
	// 			double uu_bc=uu_int+normalized_x*(pp_int-pp_bc)/(ro_int*cc_int);
	// 			double vv_bc=vv_int+normalized_y*(pp_int-pp_bc)/(ro_int*cc_int);
	// 			double ww_bc=ww_int+normalized_z*(pp_int-pp_bc)/(ro_int*cc_int);

	// 			block->block_primitive_variables_->ro_[ext_cell_idx]=2.0*ro_bc-ro_int;
	// 			block->block_primitive_variables_->uu_[ext_cell_idx]=2.0*uu_bc-uu_int;
	// 			block->block_primitive_variables_->vv_[ext_cell_idx]=2.0*vv_bc-vv_int;
	// 			block->block_primitive_variables_->ww_[ext_cell_idx]=2.0*ww_bc-ww_int;
	// 			block->block_primitive_variables_->pp_[ext_cell_idx]=2.0*pp_bc-pp_int;
	// 		}
	// 	}

	// }





}
void Updater::synchroniseUpdate(Block* block)
{

}



Updater::Updater(double gamma, std::vector<double> alpha_rk)
{
	current_stage_=0;
	gamma_=gamma;
	alpha_rk_=alpha_rk;

}

Updater::~Updater()
{

}


#endif
