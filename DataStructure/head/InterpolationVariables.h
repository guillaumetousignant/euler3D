#ifndef DATASTRUCTURE_HEAD_PrimitiveVariables_H
#define DATASTRUCTURE_HEAD_PrimitiveVariables_H

class PrimitiveVariables
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

	PrimitiveVariables();
	~PrimitiveVariables();
	
};

#endif