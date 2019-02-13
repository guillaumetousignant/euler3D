#ifndef DATASTRUCTURE_SRC_INTERPOLATIONVARIABLES_CPP
#define DATASTRUCTURE_SRC_INTERPOLATIONVARIABLES_CPP

#include "InterpolationVariables.h"

InterpolationVariables::InterpolationVariables(int n_all_cells_in_block_)
{
	(*grad_ro_)[3] = new double[n_all_cells_in_block_][3];
	(*grad_uu_)[3] = new double[n_all_cells_in_block_][3];
	(*grad_vv_)[3] = new double[n_all_cells_in_block_][3];
	(*grad_ww_)[3] = new double[n_all_cells_in_block_][3];
	(*grad_pp_)[3] = new double[n_all_cells_in_block_][3];

	limiter_ro_ = new double[n_all_cells_in_block_];
	limiter_uu_ = new double[n_all_cells_in_block_];
	limiter_vv_ = new double[n_all_cells_in_block_];
	limiter_ww_ = new double[n_all_cells_in_block_];
	limiter_pp_ = new double[n_all_cells_in_block_];


}
InterpolationVariables::~InterpolationVariables()
{
	
}

#endif