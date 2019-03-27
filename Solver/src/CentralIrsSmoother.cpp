#ifndef SOLVERSKELETON_SRC_CENTRALIRSSMOOTHER_CPP
#define SOLVERSKELETON_SRC_CENTRALIRSSMOOTHER_CPP

#include "Block.h"
#include "ResidualSmoother.h"
#include "CentralIrsSmoother.h"


#include <iostream>
using namespace std;

void CentralIrsSmoother::smoothResidual(Block* block)
{
	 cout<<"\t\t\t\tExécution smoothResidual: Central IRS Smoother: "<<endl;
	PrimitiveVariables* my_primitive_variables;
	my_primitive_variables = block -> block_primitive_variables_;

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

	Cell* my_cell;
	int ncell;
	ncell = block -> n_real_cells_in_block_;

	double* jacobi_1_ro_convective= new double[ncell];
	double* jacobi_1_uu_convective= new double[ncell];
	double* jacobi_1_vv_convective= new double[ncell];
	double* jacobi_1_ww_convective= new double[ncell];
	double* jacobi_1_pp_convective= new double[ncell];

	double* jacobi_1_ro_dissipative= new double[ncell];
	double* jacobi_1_uu_dissipative= new double[ncell];
	double* jacobi_1_vv_dissipative= new double[ncell];
	double* jacobi_1_ww_dissipative= new double[ncell];
	double* jacobi_1_pp_dissipative= new double[ncell];

	double* ro_convective_smooth= new double[ncell];
	double* uu_convective_smooth= new double[ncell];
	double* vv_convective_smooth= new double[ncell];
	double* ww_convective_smooth= new double[ncell];
	double* pp_convective_smooth= new double[ncell];

	double* ro_dissipative_smooth= new double[ncell];
	double* uu_dissipative_smooth= new double[ncell];
	double* vv_dissipative_smooth= new double[ncell];
	double* ww_dissipative_smooth= new double[ncell];
	double* pp_dissipative_smooth= new double[ncell];

	double epsilon=0.8; // espilon = 0.5 to 0.8 (Blazek p.303)
	int Na;

	int my_cell_n_faces;

	int* my_cell_2_cells_connectivity;
	int my_neighbor_cell_idx;

	for (int cell_idx=0; cell_idx<ncell; cell_idx++)
	{
		Na = block->block_cells_[cell_idx]->n_faces_per_cell_;
		jacobi_1_ro_convective[cell_idx] = (my_conv_res_ro[cell_idx] +0.)/(1.+epsilon*Na);
		jacobi_1_uu_convective[cell_idx] = (my_conv_res_uu[cell_idx] +0.)/(1.+epsilon*Na);
		jacobi_1_vv_convective[cell_idx] = (my_conv_res_vv[cell_idx] +0.)/(1.+epsilon*Na);
		jacobi_1_ww_convective[cell_idx] = (my_conv_res_ww[cell_idx] +0.)/(1.+epsilon*Na);
		jacobi_1_pp_convective[cell_idx] = (my_conv_res_pp[cell_idx] +0.)/(1.+epsilon*Na);

		jacobi_1_ro_dissipative[cell_idx] = (my_diss_res_ro[cell_idx] +0.)/(1.+epsilon*Na);
		jacobi_1_uu_dissipative[cell_idx] = (my_diss_res_uu[cell_idx] +0.)/(1.+epsilon*Na);
		jacobi_1_vv_dissipative[cell_idx] = (my_diss_res_vv[cell_idx] +0.)/(1.+epsilon*Na);
		jacobi_1_vv_dissipative[cell_idx] = (my_diss_res_ww[cell_idx] +0.)/(1.+epsilon*Na);
		jacobi_1_pp_dissipative[cell_idx] = (my_diss_res_pp[cell_idx] +0.)/(1.+epsilon*Na);
	}
	for (int cell_idx=0; cell_idx<ncell; cell_idx++)
	{
		my_cell=block->block_cells_[cell_idx];

		double sum_jacobi1_ro_convective=0.;
		double sum_jacobi1_uu_convective=0.;
		double sum_jacobi1_vv_convective=0.;
		double sum_jacobi1_ww_convective=0.;
		double sum_jacobi1_pp_convective=0.;

		double sum_jacobi1_ro_dissipative=0.;
		double sum_jacobi1_uu_dissipative=0.;
		double sum_jacobi1_vv_dissipative=0.;
		double sum_jacobi1_ww_dissipative=0.;
		double sum_jacobi1_pp_dissipative=0.;

		my_cell_n_faces=my_cell->n_faces_per_cell_;
		my_cell_2_cells_connectivity=my_cell->cell_2_cells_connectivity_;

		for (int cell_2_cells_idx = 0; cell_2_cells_idx < my_cell_n_faces; cell_2_cells_idx++)
		{
			// int cell_j = my_cell[cell_idx]->cell_2_cells_connectivity_[cell_2_cells_idx];
			my_neighbor_cell_idx = my_cell_2_cells_connectivity[cell_2_cells_idx];
			if (my_neighbor_cell_idx < ncell)
			{
				sum_jacobi1_ro_convective += jacobi_1_ro_convective[my_neighbor_cell_idx];
				sum_jacobi1_uu_convective += jacobi_1_uu_convective[my_neighbor_cell_idx];
				sum_jacobi1_vv_convective += jacobi_1_vv_convective[my_neighbor_cell_idx];
				sum_jacobi1_ww_convective += jacobi_1_ww_convective[my_neighbor_cell_idx];
				sum_jacobi1_pp_convective += jacobi_1_pp_convective[my_neighbor_cell_idx];

				sum_jacobi1_ro_dissipative += jacobi_1_ro_dissipative[my_neighbor_cell_idx];
				sum_jacobi1_uu_dissipative += jacobi_1_uu_dissipative[my_neighbor_cell_idx];
				sum_jacobi1_vv_dissipative += jacobi_1_vv_dissipative[my_neighbor_cell_idx];
				sum_jacobi1_ww_dissipative += jacobi_1_ww_dissipative[my_neighbor_cell_idx];
				sum_jacobi1_pp_dissipative += jacobi_1_pp_dissipative[my_neighbor_cell_idx];
			}
		}
		Na = block->block_cells_[cell_idx]->n_faces_per_cell_;
		ro_convective_smooth[cell_idx] = (my_conv_res_ro[cell_idx]+epsilon*sum_jacobi1_ro_convective)/(1.+epsilon*Na);
		uu_convective_smooth[cell_idx] = (my_conv_res_uu[cell_idx]+epsilon*sum_jacobi1_uu_convective)/(1.+epsilon*Na);
		vv_convective_smooth[cell_idx] = (my_conv_res_vv[cell_idx]+epsilon*sum_jacobi1_vv_convective)/(1.+epsilon*Na);
		ww_convective_smooth[cell_idx] = (my_conv_res_ww[cell_idx]+epsilon*sum_jacobi1_ww_convective)/(1.+epsilon*Na);
		pp_convective_smooth[cell_idx] = (my_conv_res_pp[cell_idx]+epsilon*sum_jacobi1_pp_convective)/(1.+epsilon*Na);

		ro_dissipative_smooth[cell_idx] = (my_diss_res_ro[cell_idx]+epsilon*sum_jacobi1_ro_dissipative)/(1.+epsilon*Na);
		uu_dissipative_smooth[cell_idx] = (my_diss_res_uu[cell_idx]+epsilon*sum_jacobi1_uu_dissipative)/(1.+epsilon*Na);
		vv_dissipative_smooth[cell_idx] = (my_diss_res_vv[cell_idx]+epsilon*sum_jacobi1_vv_dissipative)/(1.+epsilon*Na);
		ww_dissipative_smooth[cell_idx] = (my_diss_res_ww[cell_idx]+epsilon*sum_jacobi1_ww_dissipative)/(1.+epsilon*Na);
		pp_dissipative_smooth[cell_idx] = (my_diss_res_pp[cell_idx]+epsilon*sum_jacobi1_pp_dissipative)/(1.+epsilon*Na);
	}

	for (int cell_idx=0; cell_idx<ncell; cell_idx++)
	{
		my_conv_res_ro[cell_idx] = ro_convective_smooth[cell_idx];
		my_conv_res_uu[cell_idx] = uu_convective_smooth[cell_idx];
		my_conv_res_vv[cell_idx] = vv_convective_smooth[cell_idx];
		my_conv_res_ww[cell_idx] = ww_convective_smooth[cell_idx];
		my_conv_res_pp[cell_idx] = pp_convective_smooth[cell_idx];

		my_diss_res_ro[cell_idx] = ro_dissipative_smooth[cell_idx];
		my_diss_res_uu[cell_idx] = uu_dissipative_smooth[cell_idx];
		my_diss_res_vv[cell_idx] = vv_dissipative_smooth[cell_idx];
		my_diss_res_ww[cell_idx] = ww_dissipative_smooth[cell_idx];
		my_diss_res_pp[cell_idx] = pp_dissipative_smooth[cell_idx];
	}
	free(jacobi_1_ro_convective);
	free(jacobi_1_uu_convective);
	free(jacobi_1_vv_convective);
	free(jacobi_1_ww_convective);
	free(jacobi_1_pp_convective);

	free(jacobi_1_ro_dissipative);
	free(jacobi_1_uu_dissipative);
	free(jacobi_1_vv_dissipative);
	free(jacobi_1_ww_dissipative);
	free(jacobi_1_pp_dissipative);

	free(ro_convective_smooth);
	free(uu_convective_smooth);
	free(vv_convective_smooth);
	free(ww_convective_smooth);
	free(pp_convective_smooth);

	free(ro_dissipative_smooth);
	free(uu_dissipative_smooth);
	free(vv_dissipative_smooth);
	free(ww_dissipative_smooth);
	free(pp_dissipative_smooth);

}



CentralIrsSmoother::CentralIrsSmoother()
{

}

CentralIrsSmoother::~CentralIrsSmoother()
{

}


#endif
