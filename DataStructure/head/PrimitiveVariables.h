#ifndef DATASTRUCTURE_HEAD_PRIMITIVEVARIABLES_H
#define DATASTRUCTURE_HEAD_PRIMITIVEVARIABLES_H

class PrimitiveVariables
{
public:
	double* ro_;
	double* uu_;
	double* vv_;
	double* ww_;
	double* pp_;

	double* conv_res_ro_;
	double* conv_res_uu_;
	double* conv_res_vv_;
	double* conv_res_ww_;
	double* conv_res_pp_;

	double* diss_res_ro_;
	double* diss_res_uu_;
	double* diss_res_vv_;
	double* diss_res_ww_;
	double* diss_res_pp_;

	double* ro_0_;
	double* ru_0_;
	double* rv_0_;
	double* rw_0_;
	double* re_0_;

	PrimitiveVariables(int n_all_cells_in_blocks);
	~PrimitiveVariables();
	
};

#endif