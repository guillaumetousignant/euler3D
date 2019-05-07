#ifndef DATASTRUCTURE_HEAD_INTEPOLATIONVARIABLES_H
#define DATASTRUCTURE_HEAD_INTEPOLATIONVARIABLES_H

class InterpolationVariables
{
public:
	double** grad_ro_;
	double** grad_uu_;
	double** grad_vv_;
	double** grad_ww_;
	double** grad_pp_;

	double* limiter_ro_;
	double* limiter_uu_;
	double* limiter_vv_;
	double* limiter_ww_;
	double* limiter_pp_;

	InterpolationVariables(int n_all_cells_in_block);
	~InterpolationVariables();
	
};

#endif