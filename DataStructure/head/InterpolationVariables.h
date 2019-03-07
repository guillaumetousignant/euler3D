#ifndef DATASTRUCTURE_HEAD_INTEPOLATIONVARIABLES_H
#define DATASTRUCTURE_HEAD_INTEPOLATIONVARIABLES_H

class InterpolationVariables
{
public:
	double (*grad_ro_)[3];
	double (*grad_uu_)[3];
	double (*grad_vv_)[3];
	double (*grad_ww_)[3];
	double (*grad_pp_)[3];

	double* limiter_ro_;
	double* limiter_uu_;
	double* limiter_vv_;
	double* limiter_ww_;
	double* limiter_pp_;

	InterpolationVariables(int n_all_cells_in_block);
	~InterpolationVariables();
	
};

#endif