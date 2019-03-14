#ifndef DATASTRUCTURE_SRC_PRIMITIVEVARIABLES_CPP
#define DATASTRUCTURE_SRC_PRIMITIVEVARIABLES_CPP

#include "PrimitiveVariables.h"
#include <cmath>

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

// 	RÉFÉRENCE CIRCULAIRE ICI
// void PrimitiveVariables::calculateFreeVariables(Interface inter)
// {
// 	double pi, c, s;
// 	pi=atan(1.0)*4.0;
// 	gamma_= inter.gamma_interface_;
// 	alpha_rad_=inter.angle_of_attack_rad_interface_;
// 	mach_=inter.mach_interface_;
// 	c=cos(alpha_rad_);
// 	s=sin(alpha_rad_);
// 	ro_free_=1.0;//densite normalise
// 	uu_free_=mach_*sqrt(gamma_)*c;
// 	vv_free_=mach_*sqrt(gamma_)*s;
// 	ww_free_=0.0;// hypothese de cas de vol sans vent de travers, vitesse laterale nulle
// 	pp_free_=1.0;//pression normalise
// }

#endif
