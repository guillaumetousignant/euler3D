#ifndef DATASTRUCTURE_HEAD_PrimitiveVariables_H
#define DATASTRUCTURE_HEAD_PrimitiveVariables_H

class PrimitiveVariables
{
public:
	double* ro_;
	double* uu_;
	double* vv_;
	double* ww_;
	double* pp_;

	double* res_ro_;
	double* res_uu_;
	double* res_vv_;
	double* res_ww_;
	double* res_pp_;

	double* ro_0_;
	double* ru_0_;
	double* rv_0_;
	double* rw_0_;
	double* re_0_;

	PrimitiveVariables();
	~PrimitiveVariables();
	
};

#endif