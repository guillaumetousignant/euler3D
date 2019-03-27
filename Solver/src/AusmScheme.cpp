#ifndef SOLVERSKELETON_SRC_AUSMSCHEME_CPP
#define SOLVERSKELETON_SRC_AUSMSCHEME_CPP

#include "Block.h"
#include "FluxScheme.h"
#include "AusmScheme.h"

#include <math.h> 
#include <iostream>
using namespace std;

void AusmScheme::computeFluxDiss(Block* block)
{
	
	// Partie convective

	double rho_L,u_L,v_L,w_L,p_L,H_L,qq_L,V_L,c_L,rho_R,u_R,v_R,w_R,p_R,H_R,qq_R,V_R,c_R,M_L,M_R,M_L_plus,M_R_minus,M_L_R;
	double Fc_L_1,Fc_L_2,Fc_L_3,Fc_L_4,Fc_L_5,Fc_R_1,Fc_R_2,Fc_R_3,Fc_R_4,Fc_R_5;
	double flux_1_dissipative,flux_2_dissipative,flux_3_dissipative,flux_4_dissipative,flux_5_dissipative;
	double normal_norm, normalized_x, normalized_y, normalized_z;
	double* left_cell_r_vector;
	double* right_cell_r_vector;

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

	double* my_diss_res_ro;
	double* my_diss_res_uu;
	double* my_diss_res_vv;
	double* my_diss_res_ww;
	double* my_diss_res_pp;
	my_diss_res_ro = my_primitive_variables -> diss_res_ro_;
	my_diss_res_uu = my_primitive_variables -> diss_res_uu_;
	my_diss_res_vv = my_primitive_variables -> diss_res_vv_;
	my_diss_res_ww = my_primitive_variables -> diss_res_ww_;
	my_diss_res_pp = my_primitive_variables -> diss_res_pp_;

	InterpolationVariables* my_interpolation_variables;
	my_interpolation_variables=block->block_interpolation_variables_;

	double** my_grad_ro_array;
	double** my_grad_uu_array;
	double** my_grad_vv_array;
	double** my_grad_ww_array;
	double** my_grad_pp_array;

	my_grad_ro_array=my_interpolation_variables->grad_ro_;
	my_grad_uu_array=my_interpolation_variables->grad_uu_;
	my_grad_vv_array=my_interpolation_variables->grad_vv_;
	my_grad_ww_array=my_interpolation_variables->grad_ww_;
	my_grad_pp_array=my_interpolation_variables->grad_pp_;

	double* my_ro_limiters;
	double* my_uu_limiters;
	double* my_vv_limiters;
	double* my_ww_limiters;
	double* my_pp_limiters;

	my_ro_limiters = my_interpolation_variables -> limiter_ro_;
	my_uu_limiters = my_interpolation_variables -> limiter_uu_;
	my_vv_limiters = my_interpolation_variables -> limiter_vv_;
	my_ww_limiters = my_interpolation_variables -> limiter_ww_;
	my_pp_limiters = my_interpolation_variables -> limiter_pp_;

	int n_dim=3;
	double delta=0.25;

	int ncell;
	ncell = block -> n_real_cells_in_block_;

	for (int cell_idx=0; cell_idx<ncell; cell_idx++)
	{
		
		my_diss_res_ro[cell_idx] *=(1.0-current_beta_);
		my_diss_res_uu[cell_idx] *=(1.0-current_beta_);
		my_diss_res_vv[cell_idx] *=(1.0-current_beta_);
		my_diss_res_ww[cell_idx] *=(1.0-current_beta_);
		my_diss_res_pp[cell_idx] *=(1.0-current_beta_);

	}

	



	int nface, left_cell, right_cell;
	int* neighboor_cells;
	Face* my_face;
	nface = block -> n_faces_in_block_;

	for (int face_idx = 0; face_idx < nface; face_idx++)
	{

		my_face = block -> block_faces_[face_idx];
		// Get S vector
		normalized_x = block -> block_faces_[face_idx] -> face_normals_[0];
		normalized_y = block -> block_faces_[face_idx] -> face_normals_[1];
		normalized_z = block -> block_faces_[face_idx] -> face_normals_[2];
		normal_norm=sqrt(normalized_x*normalized_x+normalized_y*normalized_y+normalized_z*normalized_z);
		// Normalize S vector to n
		normalized_x/=normal_norm;
		normalized_y/=normal_norm;
		normalized_z/=normal_norm;

		neighboor_cells = my_face -> face_2_cells_connectivity_;
		left_cell = neighboor_cells[0];
		right_cell = neighboor_cells[1];

		// Left cell
		rho_L = my_ro_array[left_cell];
		u_L = my_uu_array[left_cell];
		v_L = my_vv_array[left_cell];
		w_L = my_ww_array[left_cell];
		p_L = my_pp_array[left_cell];
		left_cell_r_vector=block -> block_faces_[face_idx] -> left_cell_r_vector_;

		// Add gradient effect and limiter
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			rho_L+=my_ro_limiters[left_cell]*my_grad_ro_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			u_L+=my_uu_limiters[left_cell]*my_grad_uu_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			v_L+=my_vv_limiters[left_cell]*my_grad_vv_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			w_L+=my_ww_limiters[left_cell]*my_grad_ww_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			p_L+=my_pp_limiters[left_cell]*my_grad_pp_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
		}

		qq_L = u_L*u_L+v_L*v_L+w_L*w_L;
		H_L = (0.5*qq_L+gamma_/(gamma_-1.0)*p_L/rho_L);
		V_L = u_L*normalized_x+v_L*normalized_y+w_L*normalized_z;
		c_L=sqrt(gamma_*p_L/rho_L);

		M_L=V_L/c_L;

		if (M_L<=-1.0)
		{
			M_L_plus=0;
		}
		else if (M_L<1.0)
		{
			M_L_plus=0.25*(M_L+1.0)*(M_L+1.0);
		}
		else 
		{
			M_L_plus=M_L;
		}


		// Right cell
		rho_R = my_ro_array[right_cell];
		u_R = my_uu_array[right_cell];
		v_R = my_vv_array[right_cell];
		w_R = my_ww_array[right_cell];
		p_R = my_pp_array[right_cell];
		right_cell_r_vector=block -> block_faces_[face_idx] -> right_cell_r_vector_;

		// Add gradient effect and limiter
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			rho_R+=my_ro_limiters[right_cell]*my_grad_ro_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			u_R+=my_uu_limiters[right_cell]*my_grad_uu_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			v_R+=my_vv_limiters[right_cell]*my_grad_vv_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			w_R+=my_ww_limiters[right_cell]*my_grad_ww_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			p_R+=my_pp_limiters[right_cell]*my_grad_pp_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
		}

		qq_R = u_R*u_R+v_R*v_R+w_R*w_R;
		H_R = (0.5*qq_R+gamma_/(gamma_-1.0)*p_R/rho_R);
		V_R = u_R*normalized_x+v_R*normalized_y+w_R*normalized_z;
		c_R=sqrt(gamma_*p_R/rho_R);

		M_R=V_R/c_R;

		if (M_R<=-1.0)
		{
			M_R_minus=M_R;
		}
		else if (M_R<1.0)
		{
			M_R_minus=-0.25*(M_R-1.0)*(M_R-1.0);
		}
		else
		{
			M_R_minus=0;
		}


		M_L_R=M_L_plus+M_R_minus;


		// Correct for shocks
		if (fabs(M_L_R)>delta)
		{

		}
		else
		{	
			M_L_R=(M_L_R*M_L_R+delta*delta)/(2.0*delta);
		}

		Fc_L_1 = rho_L*c_L;
		Fc_R_1 = rho_R*c_R;
		Fc_L_2 = rho_L*u_L*c_L;
		Fc_R_2 = rho_R*u_R*c_R;
		Fc_L_3 = rho_L*v_L*c_L;
		Fc_R_3 = rho_R*v_R*c_R;
		Fc_L_4 = rho_L*w_L*c_L;
		Fc_R_4 = rho_R*w_R*c_R;
		Fc_L_5 = rho_L*H_L*c_L;
		Fc_R_5 = rho_R*H_R*c_R;


		flux_1_dissipative = 0.5*fabs(M_L_R)*(-Fc_L_1+Fc_R_1)*normal_norm;
		flux_2_dissipative = 0.5*fabs(M_L_R)*(-Fc_L_2+Fc_R_2)*normal_norm;
		flux_3_dissipative = 0.5*fabs(M_L_R)*(-Fc_L_3+Fc_R_3)*normal_norm;
		flux_4_dissipative = 0.5*fabs(M_L_R)*(-Fc_L_4+Fc_R_4)*normal_norm;
		flux_5_dissipative = 0.5*fabs(M_L_R)*(-Fc_L_5+Fc_R_5)*normal_norm;


		my_diss_res_ro[left_cell] += flux_1_dissipative*current_beta_;
		my_diss_res_uu[left_cell] += flux_2_dissipative*current_beta_;
		my_diss_res_vv[left_cell] += flux_3_dissipative*current_beta_;
		my_diss_res_ww[left_cell] += flux_4_dissipative*current_beta_;
		my_diss_res_pp[left_cell] += flux_5_dissipative*current_beta_;

		my_diss_res_ro[right_cell] -= flux_1_dissipative*current_beta_;
		my_diss_res_uu[right_cell] -= flux_2_dissipative*current_beta_;
		my_diss_res_vv[right_cell] -= flux_3_dissipative*current_beta_;
		my_diss_res_ww[right_cell] -= flux_4_dissipative*current_beta_;
		my_diss_res_pp[right_cell] -= flux_5_dissipative*current_beta_;


	}

	

	

	/*

	double flux_1_dissipative,flux_2_dissipative,flux_3_dissipative,flux_4_dissipative,flux_5_dissipative;

	for (int cell_idx=0; cell_idx<ncell; cell_idx++)
	{
		
		my_diss_res_ro[cell_idx] *=(1.0-current_beta_);
		my_diss_res_uu[cell_idx] *=(1.0-current_beta_);
		my_diss_res_vv[cell_idx] *=(1.0-current_beta_);
		my_diss_res_ww[cell_idx] *=(1.0-current_beta_);
		my_diss_res_pp[cell_idx] *=(1.0-current_beta_);

	}

	
	for (int face_idx = 0; face_idx < nface; face_idx++)
	{

		my_face = block -> block_faces_[face_idx];
		// Get S vector
		normalized_x = block -> block_faces_[face_idx] -> face_normals_[0];
		normalized_y = block -> block_faces_[face_idx] -> face_normals_[1];
		normalized_z = block -> block_faces_[face_idx] -> face_normals_[2];
		normal_norm=sqrt(normalized_x*normalized_x+normalized_y*normalized_y+normalized_z*normalized_z);
		// Normalize S vector to n
		normalized_x/=normal_norm;
		normalized_y/=normal_norm;
		normalized_z/=normal_norm;

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
		c_L=sqrt(gamma_*p_L/rho_L);
		M_L=V_L/c_L;
		if (M_L>=1.0)
		{
			p_L_plus=p_L;
		}
		else if (M_L<=-1.0)
		{
			p_L_plus=0.0;
		}
		else 
		{
			p_L_plus=p_L*0.25*(M_L+1.0)*(M_L+1.0)*(2.0-M_L);
		}
		

		// Right cell
		rho_R = my_ro_array[right_cell];
		u_R = my_uu_array[right_cell];
		v_R = my_vv_array[right_cell];
		w_R = my_ww_array[right_cell];
		p_R = my_pp_array[right_cell];
		qq_R = u_R*u_R+v_R*v_R+w_R*w_R;
		H_R = (0.5*qq_R+gamma_/(gamma_-1.0)*p_R/rho_R);
		V_R = u_R*normalized_x+v_R*normalized_y+w_R*normalized_z;
		c_R=sqrt(gamma_*p_R/rho_R);
		M_R=V_R/c_R;
		if (M_R>=1.0)
		{
			p_R_minus=0;
		}
		else if (M_R<=-1.0)
		{
			p_R_minus=p_R;
		}
		else
		{
			p_R_minus=p_R*0.25*(M_R-1.0)*(M_R-1.0)*(2.0+M_R);
		}
		


		M_L_R=(V_R/c_R+V_L/c_L)*0.5;

		Fc_L_1 = rho_L*c_L;
		Fc_R_1 = rho_R*c_R;
		Fc_L_2 = rho_L*u_L*c_L;
		Fc_R_2 = rho_R*u_R*c_R;
		Fc_L_3 = rho_L*v_L*c_L;
		Fc_R_3 = rho_R*v_R*c_R;
		Fc_L_4 = rho_L*w_L*c_L;
		Fc_R_4 = rho_R*w_R*c_R;
		Fc_L_5 = rho_L*H_L*c_L;
		Fc_R_5 = rho_R*H_R*c_R;


		flux_1_dissipative = 0.5*fabs(M_L_R)*(-Fc_L_1+Fc_R_1)*normal_norm;
		flux_2_dissipative = (0.5*fabs(M_L_R)*(-Fc_L_2+Fc_R_2)-normalized_x*(p_L_plus+p_R_minus))*normal_norm;
		flux_3_dissipative = (0.5*fabs(M_L_R)*(-Fc_L_3+Fc_R_3)-normalized_y*(p_L_plus+p_R_minus))*normal_norm;
		flux_4_dissipative = (0.5*fabs(M_L_R)*(-Fc_L_4+Fc_R_4)-normalized_z*(p_L_plus+p_R_minus))*normal_norm;
		flux_5_dissipative = 0.5*fabs(M_L_R)*(-Fc_L_5+Fc_R_5)*normal_norm;


		my_diss_res_ro[left_cell] += flux_1_dissipative*current_beta_;
		my_diss_res_uu[left_cell] += flux_2_dissipative*current_beta_;
		my_diss_res_vv[left_cell] += flux_3_dissipative*current_beta_;
		my_diss_res_ww[left_cell] += flux_4_dissipative*current_beta_;
		my_diss_res_pp[left_cell] += flux_5_dissipative*current_beta_;

		my_diss_res_ro[right_cell] -= flux_1_dissipative*current_beta_;
		my_diss_res_uu[right_cell] -= flux_2_dissipative*current_beta_;
		my_diss_res_vv[right_cell] -= flux_3_dissipative*current_beta_;
		my_diss_res_ww[right_cell] -= flux_4_dissipative*current_beta_;
		my_diss_res_pp[right_cell] -= flux_5_dissipative*current_beta_;


	}


	*/

	// FORMULATION JUSTE CONVECTIVE QUI FONCTIONNE
	/*
	// Partie convective

	double rho_L,u_L,v_L,w_L,p_L,H_L,qq_L,V_L,c_L,rho_R,u_R,v_R,w_R,p_R,H_R,qq_R,V_R,c_R,M_L,M_R,M_L_plus,M_R_minus,M_L_R, p_L_plus,p_R_minus;
	double Fc_L_1,Fc_L_2,Fc_L_3,Fc_L_4,Fc_L_5,Fc_R_1,Fc_R_2,Fc_R_3,Fc_R_4,Fc_R_5;
	double flux_1_convective,flux_2_convective,flux_3_convective,flux_4_convective,flux_5_convective;
	double normal_norm, normalized_x, normalized_y, normalized_z;
	double* left_cell_r_vector;
	double* right_cell_r_vector;

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

	InterpolationVariables* my_interpolation_variables;
	my_interpolation_variables=block->block_interpolation_variables_;

	double** my_grad_ro_array;
	double** my_grad_uu_array;
	double** my_grad_vv_array;
	double** my_grad_ww_array;
	double** my_grad_pp_array;

	my_grad_ro_array=my_interpolation_variables->grad_ro_;
	my_grad_uu_array=my_interpolation_variables->grad_uu_;
	my_grad_vv_array=my_interpolation_variables->grad_vv_;
	my_grad_ww_array=my_interpolation_variables->grad_ww_;
	my_grad_pp_array=my_interpolation_variables->grad_pp_;

	double* my_ro_limiters;
	double* my_uu_limiters;
	double* my_vv_limiters;
	double* my_ww_limiters;
	double* my_pp_limiters;

	my_ro_limiters = my_interpolation_variables -> limiter_ro_;
	my_uu_limiters = my_interpolation_variables -> limiter_uu_;
	my_vv_limiters = my_interpolation_variables -> limiter_vv_;
	my_ww_limiters = my_interpolation_variables -> limiter_ww_;
	my_pp_limiters = my_interpolation_variables -> limiter_pp_;

	int n_dim=3;

	int ncell;
	ncell = block -> n_real_cells_in_block_;

	for (int cell_idx=0; cell_idx<ncell; cell_idx++)
	{
		my_conv_res_ro[cell_idx] =0.0;
		my_conv_res_uu[cell_idx] =0.0;
		my_conv_res_vv[cell_idx] =0.0;
		my_conv_res_ww[cell_idx] =0.0;
		my_conv_res_pp[cell_idx] =0.0;

	}
	


	int nface, left_cell, right_cell;
	int* neighboor_cells;
	Face* my_face;
	nface = block -> n_faces_in_block_;

	for (int face_idx = 0; face_idx < nface; face_idx++)
	{

		my_face = block -> block_faces_[face_idx];
		// Get S vector
		normalized_x = block -> block_faces_[face_idx] -> face_normals_[0];
		normalized_y = block -> block_faces_[face_idx] -> face_normals_[1];
		normalized_z = block -> block_faces_[face_idx] -> face_normals_[2];
		normal_norm=sqrt(normalized_x*normalized_x+normalized_y*normalized_y+normalized_z*normalized_z);
		// Normalize S vector to n
		normalized_x/=normal_norm;
		normalized_y/=normal_norm;
		normalized_z/=normal_norm;

		neighboor_cells = my_face -> face_2_cells_connectivity_;
		left_cell = neighboor_cells[0];
		right_cell = neighboor_cells[1];

		// Left cell
		rho_L = my_ro_array[left_cell];
		u_L = my_uu_array[left_cell];
		v_L = my_vv_array[left_cell];
		w_L = my_ww_array[left_cell];
		p_L = my_pp_array[left_cell];
		left_cell_r_vector=block -> block_faces_[face_idx] -> left_cell_r_vector_;

		// Add gradient effect and limiter
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			rho_L+=my_ro_limiters[left_cell]*my_grad_ro_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			u_L+=my_uu_limiters[left_cell]*my_grad_uu_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			v_L+=my_vv_limiters[left_cell]*my_grad_vv_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			w_L+=my_ww_limiters[left_cell]*my_grad_ww_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			p_L+=my_pp_limiters[left_cell]*my_grad_pp_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
		}

		qq_L = u_L*u_L+v_L*v_L+w_L*w_L;
		H_L = (0.5*qq_L+gamma_/(gamma_-1.0)*p_L/rho_L);
		V_L = u_L*normalized_x+v_L*normalized_y+w_L*normalized_z;
		c_L=sqrt(gamma_*p_L/rho_L);

		M_L=V_L/c_L;

		if (M_L<=-1.0)
		{
			p_L_plus=0;
			M_L_plus=0;
		}
		else if (M_L<1.0)
		{
			p_L_plus=p_L*0.25*(M_L+1.0)*(M_L+1.0)*(2.0-M_L);
			M_L_plus=0.25*(M_L+1.0)*(M_L+1.0);
		}
		else 
		{
			M_L_plus=M_L;
			p_L_plus=p_L;
		}


		// Right cell
		rho_R = my_ro_array[right_cell];
		u_R = my_uu_array[right_cell];
		v_R = my_vv_array[right_cell];
		w_R = my_ww_array[right_cell];
		p_R = my_pp_array[right_cell];
		right_cell_r_vector=block -> block_faces_[face_idx] -> right_cell_r_vector_;

		// Add gradient effect and limiter
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			rho_R+=my_ro_limiters[right_cell]*my_grad_ro_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			u_R+=my_uu_limiters[right_cell]*my_grad_uu_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			v_R+=my_vv_limiters[right_cell]*my_grad_vv_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			w_R+=my_ww_limiters[right_cell]*my_grad_ww_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			p_R+=my_pp_limiters[right_cell]*my_grad_pp_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
		}

		qq_R = u_R*u_R+v_R*v_R+w_R*w_R;
		H_R = (0.5*qq_R+gamma_/(gamma_-1.0)*p_R/rho_R);
		V_R = u_R*normalized_x+v_R*normalized_y+w_R*normalized_z;
		c_R=sqrt(gamma_*p_R/rho_R);

		M_R=V_R/c_R;

		if (M_R<=-1.0)
		{
			p_R_minus=p_R;
			M_R_minus=M_R;
		}
		else if (M_R<1.0)
		{
			p_R_minus=p_R*0.25*(1.0-M_R)*(1.0-M_R)*(2.0+M_R);
			M_R_minus=-0.25*(M_R-1.0)*(M_R-1.0);
		}
		else
		{
			p_R_minus=0;
			M_R_minus=0;
		}


		M_L_R=M_L_plus+M_R_minus;

		Fc_L_1 = fmax(0.0,M_L_plus+M_R_minus)*rho_L*c_L;
		Fc_R_1 = fmin(0.0,M_L_plus+M_R_minus)*rho_R*c_R;
		Fc_L_2 = fmax(0.0,M_L_plus+M_R_minus)*rho_L*u_L*c_L+normalized_x*p_L_plus;
		Fc_R_2 = fmin(0.0,M_L_plus+M_R_minus)*rho_R*u_R*c_R+normalized_x*p_R_minus;
		Fc_L_3 = fmax(0.0,M_L_plus+M_R_minus)*rho_L*v_L*c_L+normalized_y*p_L_plus;
		Fc_R_3 = fmin(0.0,M_L_plus+M_R_minus)*rho_R*v_R*c_R+normalized_y*p_R_minus;
		Fc_L_4 = fmax(0.0,M_L_plus+M_R_minus)*rho_L*w_L*c_L+normalized_z*p_L_plus;
		Fc_R_4 = fmin(0.0,M_L_plus+M_R_minus)*rho_R*w_R*c_R+normalized_z*p_R_minus;
		Fc_L_5 = fmax(0.0,M_L_plus+M_R_minus)*rho_L*H_L*c_L;
		Fc_R_5 = fmin(0.0,M_L_plus+M_R_minus)*rho_R*H_R*c_R;


		
		flux_1_convective = (Fc_L_1+Fc_R_1)*normal_norm;
		flux_2_convective = (Fc_L_2+Fc_R_2)*normal_norm;
		flux_3_convective = (Fc_L_3+Fc_R_3)*normal_norm;
		flux_4_convective = (Fc_L_4+Fc_R_4)*normal_norm;
		flux_5_convective = (Fc_L_5+Fc_R_5)*normal_norm;
	

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

		//cout<<"right_cell: "<<right_cell<<" left_cell: "<<left_cell<<" face_idx: "<<face_idx<<endl;
		//cout<<"Fc_L_2 :"<<Fc_L_2<<" Fc_R_2 :"<<Fc_R_2<<" flux_2_convective: "<<flux_2_convective<<endl;
		//cout<<"M_L_plus :"<<M_L_plus<<" M_R_minus :"<<M_R_minus<<" M_L: "<<M_L<<" M_R: "<<M_R<<endl;
		//cout<<"V_L :"<<V_L<<" V_R :"<<V_R<<" c_L: "<<c_L<<" c_R: "<<c_R<<endl;
		//cout<<"rho_L :"<<rho_L<<" rho_R :"<<rho_R<<" p_L: "<<p_L<<" p_R: "<<p_R<<endl<<endl;
		

		//cout << "conv_res_ro= " << my_conv_res_ro[left_cell] << endl;
		//cout << "conv_res_uu= " << my_conv_res_uu[left_cell] << endl;
		//cout << "conv_res_vv= " << my_conv_res_vv[left_cell] << endl;
		//cout << "conv_res_ww= " << my_conv_res_ww[left_cell] << endl;
		//cout << "conv_res_pp= " << my_conv_res_pp[left_cell] << endl;
		


	}

	// Partie diffusive

	double* my_diss_res_ro;
	double* my_diss_res_uu;
	double* my_diss_res_vv;
	double* my_diss_res_ww;
	double* my_diss_res_pp;

	my_diss_res_ro = my_primitive_variables -> diss_res_ro_;
	my_diss_res_uu = my_primitive_variables -> diss_res_uu_;
	my_diss_res_vv = my_primitive_variables -> diss_res_vv_;
	my_diss_res_ww = my_primitive_variables -> diss_res_ww_;
	my_diss_res_pp = my_primitive_variables -> diss_res_pp_;

	
	// PAS DE PARTIE DIFFUSIVE

	for (int cell_idx=0; cell_idx<ncell; cell_idx++)
	{
		
		my_diss_res_ro[cell_idx] =0.0;
		my_diss_res_uu[cell_idx] =0.0;
		my_diss_res_vv[cell_idx] =0.0;
		my_diss_res_ww[cell_idx] =0.0;
		my_diss_res_pp[cell_idx] =0.0;

	}

	
	
	
	*/

	
}

void AusmScheme::computeFluxConv(Block* block)
{
	

	double rho_L,u_L,v_L,w_L,p_L,H_L,qq_L,V_L,c_L,rho_R,u_R,v_R,w_R,p_R,H_R,qq_R,V_R,c_R,M_L,M_R,M_L_plus,M_R_minus,M_L_R, p_L_plus,p_R_minus;
	double Fc_L_1,Fc_L_2,Fc_L_3,Fc_L_4,Fc_L_5,Fc_R_1,Fc_R_2,Fc_R_3,Fc_R_4,Fc_R_5;
	double flux_1_convective,flux_2_convective,flux_3_convective,flux_4_convective,flux_5_convective;
	double normal_norm, normalized_x, normalized_y, normalized_z;
	double* left_cell_r_vector;
	double* right_cell_r_vector;

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


	InterpolationVariables* my_interpolation_variables;
	my_interpolation_variables=block->block_interpolation_variables_;

	double** my_grad_ro_array;
	double** my_grad_uu_array;
	double** my_grad_vv_array;
	double** my_grad_ww_array;
	double** my_grad_pp_array;

	my_grad_ro_array=my_interpolation_variables->grad_ro_;
	my_grad_uu_array=my_interpolation_variables->grad_uu_;
	my_grad_vv_array=my_interpolation_variables->grad_vv_;
	my_grad_ww_array=my_interpolation_variables->grad_ww_;
	my_grad_pp_array=my_interpolation_variables->grad_pp_;

	double* my_ro_limiters;
	double* my_uu_limiters;
	double* my_vv_limiters;
	double* my_ww_limiters;
	double* my_pp_limiters;

	my_ro_limiters = my_interpolation_variables -> limiter_ro_;
	my_uu_limiters = my_interpolation_variables -> limiter_uu_;
	my_vv_limiters = my_interpolation_variables -> limiter_vv_;
	my_ww_limiters = my_interpolation_variables -> limiter_ww_;
	my_pp_limiters = my_interpolation_variables -> limiter_pp_;

	int n_dim=3;

	int ncell;
	ncell = block -> n_real_cells_in_block_;

	for (int cell_idx=0; cell_idx<ncell; cell_idx++)
	{
		my_conv_res_ro[cell_idx] =0.0;
		my_conv_res_uu[cell_idx] =0.0;
		my_conv_res_vv[cell_idx] =0.0;
		my_conv_res_ww[cell_idx] =0.0;
		my_conv_res_pp[cell_idx] =0.0;
	}

	



	int nface, left_cell, right_cell;
	int* neighboor_cells;
	Face* my_face;
	nface = block -> n_faces_in_block_;

	for (int face_idx = 0; face_idx < nface; face_idx++)
	{

		my_face = block -> block_faces_[face_idx];
		// Get S vector
		normalized_x = block -> block_faces_[face_idx] -> face_normals_[0];
		normalized_y = block -> block_faces_[face_idx] -> face_normals_[1];
		normalized_z = block -> block_faces_[face_idx] -> face_normals_[2];
		normal_norm=sqrt(normalized_x*normalized_x+normalized_y*normalized_y+normalized_z*normalized_z);
		// Normalize S vector to n
		normalized_x/=normal_norm;
		normalized_y/=normal_norm;
		normalized_z/=normal_norm;

		neighboor_cells = my_face -> face_2_cells_connectivity_;
		left_cell = neighboor_cells[0];
		right_cell = neighboor_cells[1];

		// Left cell
		rho_L = my_ro_array[left_cell];
		u_L = my_uu_array[left_cell];
		v_L = my_vv_array[left_cell];
		w_L = my_ww_array[left_cell];
		p_L = my_pp_array[left_cell];
		left_cell_r_vector=block -> block_faces_[face_idx] -> left_cell_r_vector_;

		// Add gradient effect and limiter
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			rho_L+=my_ro_limiters[left_cell]*my_grad_ro_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			u_L+=my_uu_limiters[left_cell]*my_grad_uu_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			v_L+=my_vv_limiters[left_cell]*my_grad_vv_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			w_L+=my_ww_limiters[left_cell]*my_grad_ww_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
			p_L+=my_pp_limiters[left_cell]*my_grad_pp_array[left_cell][dim_idx]*left_cell_r_vector[dim_idx];
		}

		qq_L = u_L*u_L+v_L*v_L+w_L*w_L;
		H_L = (0.5*qq_L+gamma_/(gamma_-1.0)*p_L/rho_L);
		V_L = u_L*normalized_x+v_L*normalized_y+w_L*normalized_z;
		c_L=sqrt(gamma_*p_L/rho_L);

		M_L=V_L/c_L;

		if (M_L<=-1.0)
		{
			p_L_plus=0;
			M_L_plus=0;
		}
		else if (M_L<1.0)
		{
			p_L_plus=p_L*0.25*(M_L+1.0)*(M_L+1.0)*(2.0-M_L);
			M_L_plus=0.25*(M_L+1.0)*(M_L+1.0);
		}
		else 
		{
			M_L_plus=M_L;
			p_L_plus=p_L;
		}


		// Right cell
		rho_R = my_ro_array[right_cell];
		u_R = my_uu_array[right_cell];
		v_R = my_vv_array[right_cell];
		w_R = my_ww_array[right_cell];
		p_R = my_pp_array[right_cell];
		right_cell_r_vector=block -> block_faces_[face_idx] -> right_cell_r_vector_;

		// Add gradient effect and limiter
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			rho_R+=my_ro_limiters[right_cell]*my_grad_ro_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			u_R+=my_uu_limiters[right_cell]*my_grad_uu_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			v_R+=my_vv_limiters[right_cell]*my_grad_vv_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			w_R+=my_ww_limiters[right_cell]*my_grad_ww_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
			p_R+=my_pp_limiters[right_cell]*my_grad_pp_array[right_cell][dim_idx]*right_cell_r_vector[dim_idx];
		}

		qq_R = u_R*u_R+v_R*v_R+w_R*w_R;
		H_R = (0.5*qq_R+gamma_/(gamma_-1.0)*p_R/rho_R);
		V_R = u_R*normalized_x+v_R*normalized_y+w_R*normalized_z;
		c_R=sqrt(gamma_*p_R/rho_R);

		M_R=V_R/c_R;

		if (M_R<=-1.0)
		{
			p_R_minus=p_R;
			M_R_minus=M_R;
		}
		else if (M_R<1.0)
		{
			p_R_minus=p_R*0.25*(1.0-M_R)*(1.0-M_R)*(2.0+M_R);
			M_R_minus=-0.25*(M_R-1.0)*(M_R-1.0);
		}
		else
		{
			p_R_minus=0;
			M_R_minus=0;
		}


		M_L_R=M_L_plus+M_R_minus;

		Fc_L_1 = rho_L*c_L;
		Fc_R_1 = rho_R*c_R;
		Fc_L_2 = rho_L*u_L*c_L;
		Fc_R_2 = rho_R*u_R*c_R;
		Fc_L_3 = rho_L*v_L*c_L;
		Fc_R_3 = rho_R*v_R*c_R;
		Fc_L_4 = rho_L*w_L*c_L;
		Fc_R_4 = rho_R*w_R*c_R;
		Fc_L_5 = rho_L*H_L*c_L;
		Fc_R_5 = rho_R*H_R*c_R;

		
		flux_1_convective = 0.5*M_L_R*(Fc_L_1+Fc_R_1)*normal_norm;
		flux_2_convective = 0.5*M_L_R*(Fc_L_2+Fc_R_2)*normal_norm+normalized_x*(p_L_plus+p_R_minus)*normal_norm;
		flux_3_convective = 0.5*M_L_R*(Fc_L_3+Fc_R_3)*normal_norm+normalized_y*(p_L_plus+p_R_minus)*normal_norm;
		flux_4_convective = 0.5*M_L_R*(Fc_L_4+Fc_R_4)*normal_norm+normalized_z*(p_L_plus+p_R_minus)*normal_norm;
		flux_5_convective = 0.5*M_L_R*(Fc_L_5+Fc_R_5)*normal_norm;
	

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
}


AusmScheme::AusmScheme(double gamma)
{
	gamma_ = gamma;
	current_beta_=1.0;
}

AusmScheme::~AusmScheme()
{

}


#endif
