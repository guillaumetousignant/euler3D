#ifndef DATASTRUCTURE_SRC_TIMEVARIABLES_CPP
#define DATASTRUCTURE_SRC_TIMEVARIABLES_CPP

#include "TimeVariables.h"

TimeVariables::TimeVariables(int n_all_cells_in_blocks)
{
	dt_ = new double[n_all_cells_in_blocks];
	(*spectral_radius_)[3] = new double[n_all_cells_in_blocks][3];
}
TimeVariables::~TimeVariables()
{
	
}

#endif