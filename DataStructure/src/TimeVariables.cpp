#ifndef DATASTRUCTURE_SRC_TIMEVARIABLES_CPP
#define DATASTRUCTURE_SRC_TIMEVARIABLES_CPP

#include "TimeVariables.h"

TimeVariables::TimeVariables(int n_real_cells_in_block):dt_(nullptr),spectral_radius_(nullptr)
{

	dt_ = new double[n_real_cells_in_block]();
	spectral_radius_ = new double[n_real_cells_in_block]();



}

TimeVariables::~TimeVariables()
{

}

#endif
