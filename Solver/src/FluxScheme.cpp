#ifndef SOLVERSKELETON_SRC_FLUXSCHEME_CPP
#define SOLVERSKELETON_SRC_FLUXSCHEME_CPP

#include "Block.h"
#include "FluxScheme.h"
#include <math.h>

#include <iostream>
using namespace std;

void FluxScheme::computeFluxDiss(Block* block)
{

}

void FluxScheme::computeFluxConv(Block* block)
{
	cout<<"\t\t\t\tExécution computeFluxConv: "<<endl;


	//Set variables
	double rho_L,u_L,v_L,w_L,p_L,H_L,qq_L,V_L,rho_R,u_R,v_R,w_R,p_R,H_R,qq_R,V_R;
	double Fc_L_1,Fc_L_2,Fc_L_3,Fc_L_4,Fc_L_5,Fc_R_1,Fc_R_2,Fc_R_3,Fc_R_4,Fc_R_5;
	double flux_1_convective,flux_2_convective,flux_3_convective,flux_4_convective,flux_5_convective;
	double normal_norm, normalized_x, normalized_y, normalized_z;

	PrimitiveVariables* my_primitive_variables;
	my_primitive_variables = block -> block_primitive_variables_;

	double* my_ro_array;
	double* my_uu_array;
	double* my_vv_array;
	double* my_ww_array;
	double* my_pp_array;
	my_ro_array = my_primitive_variables -> ro_;
	my_uu_array = my_primitive_variables -> uu_;
	my_vv_array = my_primitive_variables -> vv_;
	my_ww_array = my_primitive_variables -> ww_;
	my_pp_array = my_primitive_variables -> pp_;

	double* my_conv_res_ro;
	double* my_conv_res_uu;
	double* my_conv_res_vv;
	double* my_conv_res_ww;
	double* my_conv_res_pp;
	my_conv_res_ro = my_primitive_variables -> conv_res_ro_;
	my_conv_res_uu = my_primitive_variables -> conv_res_uu_;
	my_conv_res_vv = my_primitive_variables -> conv_res_vv_;
	my_conv_res_ww = my_primitive_variables -> conv_res_ww_;
	my_conv_res_pp = my_primitive_variables -> conv_res_pp_;

	int nface, left_cell, right_cell; // my_face,
	int* neighboor_cells;
	Face* my_face;
	// my_faces = block -> block_faces_;
	nface = block -> n_faces_in_block_;

	for (int face_idx = 0; face_idx < nface; face_idx++)
	{

		my_face = block -> block_faces_[face_idx];

		normalized_x = block -> block_faces_[face_idx] -> face_normals_[0];
		normalized_y = block -> block_faces_[face_idx] -> face_normals_[1];
		normalized_z = block -> block_faces_[face_idx] -> face_normals_[2];
		normal_norm=sqrt(normalized_x*normalized_x+normalized_y*normalized_y+normalized_z*normalized_z);

		neighboor_cells = my_face -> face_2_cells_connectivity_;
		left_cell = neighboor_cells[0];
		right_cell = neighboor_cells[1];

		// Left cell
		rho_L = my_ro_array[left_cell];
		u_L = my_uu_array[left_cell];
		v_L = my_vv_array[left_cell];
		w_L = my_ww_array[left_cell];
		p_L = my_pp_array[left_cell];
		qq_L = u_L*u_L+v_L*v_L+w_L*w_L;
		H_L = (0.5*qq_L+gamma_/(gamma_-1.0)*p_L/rho_L);
		V_L = u_L*normalized_x+v_L*normalized_y+w_L*normalized_z;

		// Right cell
		rho_R = my_ro_array[right_cell];
		u_R = my_uu_array[right_cell];
		v_R = my_vv_array[right_cell];
		w_R = my_ww_array[right_cell];
		p_R = my_pp_array[right_cell];
		qq_R = u_R*u_R+v_R*v_R+w_R*w_R;
		H_R = (0.5*qq_R+gamma_/(gamma_-1.0)*p_R/rho_R);
		V_R = u_R*normalized_x+v_R*normalized_y+w_R*normalized_z;

		Fc_L_1 = rho_L*V_L;
		Fc_R_1 = rho_R*V_R;
		Fc_L_2 = rho_L*u_L*V_L+normalized_x*p_L;
		Fc_R_2 = rho_R*u_R*V_R+normalized_x*p_R;
		Fc_L_3 = rho_L*v_L*V_L+normalized_y*p_L;
		Fc_R_3 = rho_R*v_R*V_R+normalized_y*p_R;
		Fc_L_4 = rho_L*w_L*V_L+normalized_z*p_L;
		Fc_R_4 = rho_R*w_R*V_R+normalized_z*p_R;
		Fc_L_5 = rho_L*H_L*V_L;
		Fc_R_5 = rho_R*H_R*V_R;

		flux_1_convective = 0.5*(Fc_L_1+Fc_R_1)*normal_norm;
		flux_2_convective = 0.5*(Fc_L_2+Fc_R_2)*normal_norm;
		flux_3_convective = 0.5*(Fc_L_3+Fc_R_3)*normal_norm;
		flux_4_convective = 0.5*(Fc_L_4+Fc_R_4)*normal_norm;
		flux_5_convective = 0.5*(Fc_L_5+Fc_R_5)*normal_norm;

		my_conv_res_ro[left_cell] += flux_1_convective;
		my_conv_res_uu[left_cell] += flux_2_convective;
		my_conv_res_vv[left_cell] += flux_3_convective;
		my_conv_res_ww[left_cell] += flux_4_convective;
		my_conv_res_pp[left_cell] += flux_5_convective;

		my_conv_res_ro[right_cell] -= flux_1_convective;
		my_conv_res_uu[right_cell] -= flux_2_convective;
		my_conv_res_vv[right_cell] -= flux_3_convective;
		my_conv_res_ww[right_cell] -= flux_4_convective;
		my_conv_res_pp[right_cell] -= flux_5_convective;
	}

	Cell* my_cell;
	// my_cells = block -> block_cells_;
	int ncell;//, my_cell;
	ncell = block -> n_real_cells_in_block_;
	double cell_volume;

	for (int cell_idx=0; cell_idx<ncell; cell_idx++)
	{
		my_cell = block -> block_cells_[cell_idx];
		cell_volume  = my_cell -> cell_volume_;

		my_conv_res_ro[cell_idx] /= cell_volume;
		my_conv_res_uu[cell_idx] /= cell_volume;
		my_conv_res_vv[cell_idx] /= cell_volume;
		my_conv_res_ww[cell_idx] /= cell_volume;
		my_conv_res_pp[cell_idx] /= cell_volume;
	}


}


FluxScheme::FluxScheme()
{

}

FluxScheme::~FluxScheme()
{

}


#endif
