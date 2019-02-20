#ifndef DATASTRUCTURE_SRC_PRIMITIVEVARIABLES_CPP
#define DATASTRUCTURE_SRC_PRIMITIVEVARIABLES_CPP

#include "PrimitiveVariables.h"

PrimitiveVariables::PrimitiveVariables(int n_all_cells_in_blocks)
{

	ro_ = new double[n_all_cells_in_blocks];
	uu_ = new double[n_all_cells_in_blocks];
	vv_ = new double[n_all_cells_in_blocks];
	ww_ = new double[n_all_cells_in_blocks];
	pp_ = new double[n_all_cells_in_blocks];

	conv_res_ro_ = new double[n_all_cells_in_blocks];
	conv_res_uu_ = new double[n_all_cells_in_blocks];
	conv_res_vv_ = new double[n_all_cells_in_blocks];
	conv_res_ww_ = new double[n_all_cells_in_blocks];
	conv_res_pp_ = new double[n_all_cells_in_blocks];

	diss_res_ro_ = new double[n_all_cells_in_blocks];
	diss_res_uu_ = new double[n_all_cells_in_blocks];
	diss_res_vv_ = new double[n_all_cells_in_blocks];
	diss_res_ww_ = new double[n_all_cells_in_blocks];
	diss_res_pp_ = new double[n_all_cells_in_blocks];

	ro_0_ = new double[n_all_cells_in_blocks];
	ru_0_ = new double[n_all_cells_in_blocks];
	rv_0_ = new double[n_all_cells_in_blocks];
	rw_0_ = new double[n_all_cells_in_blocks];
	re_0_ = new double[n_all_cells_in_blocks];

}
PrimitiveVariables::~PrimitiveVariables()
{
	
}

#endif