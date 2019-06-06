#ifndef DATASTRUCTURE_HEAD_PRIMITIVEVARIABLES_H
#define DATASTRUCTURE_HEAD_PRIMITIVEVARIABLES_H


//#include "Interface.h"
class PrimitiveVariables
{
public:
	double* ro_;
	double* uu_;
	double* vv_;
	double* ww_;
	double* pp_;

	double* filtered_ro_;
	double* filtered_uu_;
	double* filtered_vv_;
	double* filtered_ww_;
	double* filtered_pp_;

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

	double ro_free_;
	double uu_free_;
	double vv_free_;
	double ww_free_;
	double pp_free_;
	double gamma_;
	double alpha_deg_;
	double alpha_rad_;
	double mach_;


	PrimitiveVariables(int n_all_cells_in_blocks);
	void calculateFreeVariables(double gamma_interface, double angle_of_attack_deg_interface, double mach_interface);
	void initializeFlowField(int n_all_cells_in_blocks);

	~PrimitiveVariables();

};

#endif
