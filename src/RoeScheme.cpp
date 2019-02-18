#ifndef SOLVERSKELETON_SRC_ROESCHEME_CPP
#define SOLVERSKELETON_SRC_ROESCHEME_CPP

#include "Block.h"
#include "FluxScheme.h"
#include "RoeScheme.h"
#include <math.h>

#include <iostream>
using namespace std;

void RoeScheme::computeFlux(Block* block)
{
	block->test_block_++;
	cout<<"\t\t\t\tExécution computeFlux: Roe: "<<block->test_block_<<endl;

	//Set variables
	int left_cell,right_cell;
	double rho_L,u_L,v_L,w_L,p_L,H_L,qq_L,V_L,rho_R,u_R,v_R,w_R,p_R,H_R,qq_R,V_R;
	double delta_p,delta_V,delta_rho,delta_u,delta_v,delta_w;
	double rho_wave,u_wave,v_wave,w_wave,H_wave,c_wave,V_wave,q_square_wave;
	double F_1_cst,F_1_mass,F_1_u,F_1_v,F_1_w,F_1_energy;
	double F_234_cst,F_234_mass,F_234_u,F_234_v,F_234_w,F_234_energy;
	double F_5_cst,F_5_mass,F_5_u,F_5_v,F_5_w,F_5_energy;
	double A_roe_mass,A_roe_u,A_roe_v,A_roe_w,A_roe_energy;
	double Fc_L_1,Fc_L_2,Fc_L_3,Fc_L_4,Fc_L_5,Fc_R_1,Fc_R_2,Fc_R_3,Fc_R_4,Fc_R_5;
	double flux_1_convective,flux_2_convective,flux_3_convective,flux_4_convective,flux_5_convective;
	double flux_1_dissipative,flux_2_dissipative,flux_3_dissipative,flux_4_dissipative,flux_5_dissipative;
	double normal_norm, normalized_x, normalized_y, normalized_z;
	double LAMBDA1,LAMBDA234,LAMBDA5;

	PrimitiveVariables* my_primitive_variables;
	my_primitive_variables = block -> block_primitive_variables_;

	double* my_ro_array,my_uu_array,my_vv_array,my_ww_array,my_pp_array;
	my_ro_array = my_primitive_variables -> ro_;
	my_uu_array = my_primitive_variables -> uu_;
	my_vv_array = my_primitive_variables -> vv_;
	my_ww_array = my_primitive_variables -> ww_;
	my_pp_array = my_primitive_variables -> pp_;

	int nface;
	Face* my_faces;
	my_faces = block -> block_faces_;
	nface = block -> n_faces_in_block_;

	for (int face_idx = 0; face_idx < nface; face_idx++)
	{

		my_face = my_faces[face_idx];

		normalized_x = block -> block_faces_[my_face] -> face_normals_[0];
		normalized_y = block -> block_faces_[my_face] -> face_normals_[1];
		normalized_z = block -> block_faces_[my_face] -> face_normals_[2];
		normal_norm=sqrt(normalized_x*normalized_x+normalized_y*normalized_y+normalized_z*normalized_z);

		neighboor_cells = my_face -> face_2_cells;
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
		// !!!! DO WE USE c_wave OR local speed of sound?
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

		flux_1_dissipative = 0.5*(-A_roe_mass)*normal_norm;
		flux_2_dissipative = 0.5*(-A_roe_u)*normal_norm;
		flux_3_dissipative = 0.5*(-A_roe_v)*normal_norm;
		flux_4_dissipative = 0.5*(-A_roe_w)*normal_norm;
		flux_5_dissipative = 0.5*(-A_roe_energy)*normal_norm;

	}

	//Il manque la distribution des flux ici - on sépare convectif et dissipatif
}



RoeScheme::RoeScheme(double gamma)
{
	gamma_ = gamma;
}

RoeScheme::~RoeScheme()
{

}


#endif
