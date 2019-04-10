#ifndef DATASTRUCTURE_SRC_PRIMITIVEVARIABLES_CPP
#define DATASTRUCTURE_SRC_PRIMITIVEVARIABLES_CPP

#include "PrimitiveVariables.h"
#include <cmath>

PrimitiveVariables::PrimitiveVariables(int n_all_cells_in_blocks)
{

	ro_ = new double[n_all_cells_in_blocks]();
	uu_ = new double[n_all_cells_in_blocks]();
	vv_ = new double[n_all_cells_in_blocks]();
	ww_ = new double[n_all_cells_in_blocks]();
	pp_ = new double[n_all_cells_in_blocks]();

	conv_res_ro_ = new double[n_all_cells_in_blocks]();
	conv_res_uu_ = new double[n_all_cells_in_blocks]();
	conv_res_vv_ = new double[n_all_cells_in_blocks]();
	conv_res_ww_ = new double[n_all_cells_in_blocks]();
	conv_res_pp_ = new double[n_all_cells_in_blocks]();

	diss_res_ro_ = new double[n_all_cells_in_blocks]();
	diss_res_uu_ = new double[n_all_cells_in_blocks]();
	diss_res_vv_ = new double[n_all_cells_in_blocks]();
	diss_res_ww_ = new double[n_all_cells_in_blocks]();
	diss_res_pp_ = new double[n_all_cells_in_blocks]();

	ro_0_ = new double[n_all_cells_in_blocks]();
	ru_0_ = new double[n_all_cells_in_blocks]();
	rv_0_ = new double[n_all_cells_in_blocks]();
	rw_0_ = new double[n_all_cells_in_blocks]();
	re_0_ = new double[n_all_cells_in_blocks]();

}
PrimitiveVariables::~PrimitiveVariables()
{

}


void PrimitiveVariables::calculateFreeVariables(double gamma_interface, double angle_of_attack_deg_interface, double mach_interface)
{
	double pi, c, s;
	pi=atan(1.0)*4.0;
	gamma_= gamma_interface;
	alpha_deg_=angle_of_attack_deg_interface;
	alpha_rad_=angle_of_attack_deg_interface*pi/180.0;
	mach_=mach_interface;
	c=cos(alpha_rad_);
	s=sin(alpha_rad_);
	ro_free_=1.0;//densite normalise
	uu_free_=mach_*sqrt(gamma_)*c;
	vv_free_=0.0;
	ww_free_=mach_*sqrt(gamma_)*s;// hypothese de cas de vol sans vent de travers, vitesse laterale nulle
	pp_free_=1.0;//pression normalise
}

void PrimitiveVariables::initializeFlowField(int n_all_cells_in_blocks)
{
	for(int i=0; i<n_all_cells_in_blocks;i++)
	{
		ro_[i]=ro_free_;
		uu_[i]=uu_free_;
		vv_[i]=vv_free_;
		ww_[i]=ww_free_;
		pp_[i]=pp_free_;
	}

}

#endif
