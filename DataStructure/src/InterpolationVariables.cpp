#ifndef DATASTRUCTURE_SRC_INTERPOLATIONVARIABLES_CPP
#define DATASTRUCTURE_SRC_INTERPOLATIONVARIABLES_CPP

#include "InterpolationVariables.h"

InterpolationVariables::InterpolationVariables(int n_all_cells_in_block)
{
	grad_ro_ = new double[n_all_cells_in_block][3];
	grad_uu_ = new double[n_all_cells_in_block][3];
	grad_vv_ = new double[n_all_cells_in_block][3];
	grad_ww_ = new double[n_all_cells_in_block][3];
	grad_pp_ = new double[n_all_cells_in_block][3];

	limiter_ro_ = new double[n_all_cells_in_block];
	limiter_uu_ = new double[n_all_cells_in_block];
	limiter_vv_ = new double[n_all_cells_in_block];
	limiter_ww_ = new double[n_all_cells_in_block];
	limiter_pp_ = new double[n_all_cells_in_block];


}
InterpolationVariables::~InterpolationVariables()
{
	
}

#endif