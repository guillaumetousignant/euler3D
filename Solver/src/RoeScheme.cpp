#ifndef SOLVERSKELETON_SRC_ROESCHEME_CPP
#define SOLVERSKELETON_SRC_ROESCHEME_CPP

#include "Block.h"
#include "FluxScheme.h"
#include "RoeScheme.h"
#include <math.h>

#include <iostream>
using namespace std;

void RoeScheme::computeFluxDiss(Block* block)
{
	//cout<<"\t\t\t\tExécution computeFluxDiss: Roe: "<<endl;

	//Set variables
	double rho_L,u_L,v_L,w_L,p_L,H_L,qq_L,V_L,rho_R,u_R,v_R,w_R,p_R,H_R,qq_R,V_R;
	double delta_p,delta_V,delta_rho,delta_u,delta_v,delta_w;
	double rho_wave,u_wave,v_wave,w_wave,H_wave,c_wave,V_wave,q_square_wave;
	double F_1_cst,F_1_mass,F_1_u,F_1_v,F_1_w,F_1_energy;
	double F_234_cst,F_234_mass,F_234_u,F_234_v,F_234_w,F_234_energy;
	double F_5_cst,F_5_mass,F_5_u,F_5_v,F_5_w,F_5_energy;
	double A_roe_mass,A_roe_u,A_roe_v,A_roe_w,A_roe_energy;
	double flux_1_dissipative,flux_2_dissipative,flux_3_dissipative,flux_4_dissipative,flux_5_dissipative;
	double normal_norm, normalized_x, normalized_y, normalized_z;
	double LAMBDA1,LAMBDA234,LAMBDA5;
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

	// my_cells = block -> block_cells_;
	int ncell; // my_cell;
	ncell = block -> n_real_cells_in_block_;
	
	for (int cell_idx=0; cell_idx<ncell; cell_idx++)
	{
		
		my_diss_res_ro[cell_idx] *=(1.0-current_beta_);
		my_diss_res_uu[cell_idx] *=(1.0-current_beta_);
		my_diss_res_vv[cell_idx] *=(1.0-current_beta_);
		my_diss_res_ww[cell_idx] *=(1.0-current_beta_);
		my_diss_res_pp[cell_idx] *=(1.0-current_beta_);

	}
	
	

	int nface, left_cell, right_cell; // my_face,
	int* neighboor_cells;
	Face* my_face;
	// my_faces = block -> block_faces_;
	nface = block -> n_faces_in_block_;

	int n_dim=3;

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

		//Computation of delta's
		delta_p = (p_R-p_L);
		delta_V = (V_R-V_L);
		delta_rho = (rho_R-rho_L);
		delta_u = (u_R-u_L);
		delta_v = (v_R-v_L);
		delta_w = (w_R-w_L);

		// Starts computation
		rho_wave = sqrt(rho_L*rho_R);
		u_wave = (u_L*sqrt(rho_L)+u_R*sqrt(rho_R))/(sqrt(rho_L)+sqrt(rho_R));
		v_wave = (v_L*sqrt(rho_L)+v_R*sqrt(rho_R))/(sqrt(rho_L)+sqrt(rho_R));
		w_wave = (w_L*sqrt(rho_L)+w_R*sqrt(rho_R))/(sqrt(rho_L)+sqrt(rho_R));
		H_wave = (H_L*sqrt(rho_L)+H_R*sqrt(rho_R))/(sqrt(rho_L)+sqrt(rho_R));
		q_square_wave = u_wave*u_wave+v_wave*v_wave+w_wave*w_wave;
		c_wave = sqrt((gamma_-1.)*(H_wave-q_square_wave/2.));
		V_wave = u_wave*normalized_x+v_wave*normalized_y+w_wave*normalized_z;

		// Harten's correction
		double delta=1./10.*c_wave; //Harten's delta
		if (fabs(V_wave-c_wave)<=delta)
		{
			LAMBDA1 = (fabs(V_wave-c_wave)*fabs(V_wave-c_wave)+delta*delta)/(2.*delta);
		}
		else
		{
			LAMBDA1 = fabs(V_wave-c_wave);
		}
		if (fabs(V_wave)<=delta)
		{
			LAMBDA234 = (fabs(V_wave)*fabs(V_wave)+delta*delta)/(2.*delta);
		}
		else
		{
			LAMBDA234 = fabs(V_wave);
		}
		if (fabs(V_wave+c_wave)<=delta)
		{
			LAMBDA5 = (fabs(V_wave+c_wave)*fabs(V_wave+c_wave)+delta*delta)/(2.*delta);
		}
		else
		{
			LAMBDA5 = fabs(V_wave+c_wave);
		}

		// Computation of F1
		F_1_cst = LAMBDA1*(delta_p-rho_wave*c_wave*delta_V)/(2.*c_wave*c_wave);
		F_1_mass = F_1_cst*1.;
		F_1_u = F_1_cst*(u_wave-c_wave*normalized_x);
		F_1_v = F_1_cst*(v_wave-c_wave*normalized_y);
		F_1_w = F_1_cst*(w_wave-c_wave*normalized_z);
		F_1_energy = F_1_cst*(H_wave-c_wave*V_wave);

		// Computation of F_234
		F_234_cst = (delta_rho-delta_p/(c_wave*c_wave));
		F_234_mass = LAMBDA234*(F_234_cst*1.+rho_wave*0.);
		F_234_u = LAMBDA234*((F_234_cst*u_wave)+rho_wave*(delta_u-delta_V*normalized_x));
		F_234_v = LAMBDA234*((F_234_cst*v_wave)+rho_wave*(delta_v-delta_V*normalized_y));
		F_234_w = LAMBDA234*((F_234_cst*w_wave)+rho_wave*(delta_w-delta_V*normalized_z));
		F_234_energy = LAMBDA234*((F_234_cst*q_square_wave/2.)+rho_wave*(u_wave*delta_u+v_wave*delta_v+w_wave*delta_w-V_wave*delta_V));

		// Compuatation of F_5
		F_5_cst = LAMBDA5*(delta_p+rho_wave*c_wave*delta_V)/(2.*c_wave*c_wave);
		F_5_mass = F_5_cst*1.;
		F_5_u = F_5_cst*(u_wave+c_wave*normalized_x);
		F_5_v = F_5_cst*(v_wave+c_wave*normalized_y);
		F_5_w = F_5_cst*(w_wave+c_wave*normalized_z);
		F_5_energy = F_5_cst*(H_wave+c_wave*V_wave);

		// Computation of A_roe
		A_roe_mass = F_1_mass + F_234_mass + F_5_mass;
		A_roe_u = F_1_u + F_234_u + F_5_u;
		A_roe_v = F_1_v + F_234_v + F_5_v;
		A_roe_w = F_1_w + F_234_w + F_5_w;
		A_roe_energy = F_1_energy + F_234_energy + F_5_energy;

		flux_1_dissipative = 0.5*(A_roe_mass)*normal_norm;
		flux_2_dissipative = 0.5*(A_roe_u)*normal_norm;
		flux_3_dissipative = 0.5*(A_roe_v)*normal_norm;
		flux_4_dissipative = 0.5*(A_roe_w)*normal_norm;
		flux_5_dissipative = 0.5*(A_roe_energy)*normal_norm;
		

		/*
		if ((left_cell>=block->n_real_cells_in_block_)&&(block->block_id_==0))
		{
			cout<<"Flux 1 left diss cell 266: "<< left_cell<<" "<<rho_L<<" "<< u_L<<" "<< v_L<<" "<<w_L<<" "<<p_L<<endl;
		}
		if ((right_cell>=block->n_real_cells_in_block_)&&(block->block_id_==0))
		{
			cout<<"Flux 1 left diss cell 266: "<< right_cell<<" "<<rho_R<<" "<< u_R<<" "<< v_R<<" "<<w_R<<" "<<p_R<<endl;
		}
		*/

		//if (fabs(normalized_z)<0.5)
		//{
			//cout<<"fluxes: "<<face_idx<<" "<<normalized_x<<" "<<normalized_y<<" "<<normal_norm<<endl;
			//cout<<flux_1_dissipative<<" "<<flux_2_dissipative<<" "<<flux_3_dissipative<<" "<<flux_5_dissipative<<endl;
			//cout<<F_1_u<<" "<<F_234_u<<" "<<F_5_u<<endl<<endl;
			//cout<<my_diss_res_uu[left_cell]<<" "<<my_diss_res_uu[right_cell]<<endl;
			//cout<<current_beta_<<endl<<endl;


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
		//}
		
		
	}


	
	for (int cell_idx=0; cell_idx<ncell; cell_idx++)
	{
		cout << "=================================================" << endl;
		cout << "Block id: "<<block->block_id_<<" Cellule id=" << cell_idx << endl;
		
		
		//cout << "diss_res_ro= " << my_diss_res_ro[cell_idx] << endl;
		//cout << "diss_res_uu= " << my_diss_res_uu[cell_idx] << endl;
		//cout << "diss_res_vv= " << my_diss_res_vv[cell_idx] << endl;
		//cout << "diss_res_ww= " << my_diss_res_ww[cell_idx] << endl;
		cout << "diss_res_pp= " << my_diss_res_pp[cell_idx] << endl;
		

	}
	

}



RoeScheme::RoeScheme(double gamma)
{
	gamma_ = gamma;
	current_beta_=1.0;
}

RoeScheme::~RoeScheme()
{

}


#endif
