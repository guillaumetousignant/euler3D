#include "Interface.h"

#include <string>
#include <iostream>
using namespace std;

Interface::Interface(string mesh_file_name, string topology_file_name, double gamma, double cfl, int stage_number, double *alpha_rk, double *beta_rk,string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, string residual_smoother_choice)
{
	mesh_file_name_interface_=mesh_file_name;
	topology_file_name_interface_=topology_file_name;
	gamma_interface_=gamma;
	cfl_interface_=cfl;
	stage_number_interface_=stage_number;
	alpha_rk_interface_=alpha_rk;
	beta_rk_interface_=beta_rk;
	interpolation_choice_interface_=interpolation_choice;
	gradient_choice_interface_=gradient_choice;
	limiter_choice_interface_=limiter_choice;
	flux_scheme_choice_interface_=flux_scheme_choice;
	residual_smoother_choice_interface_=residual_smoother_choice;
}


Interface::Interface()
{	
	mesh_file_name_interface_="default_mesh.txt";
	topology_file_name_interface_="default_topology.txt";
	gamma_interface_=1.5;
	cfl_interface_=1.0;
	stage_number_interface_=5;
	double alpha_rk[5]={420,420,420,420,420};
	double beta_rk[5]={1337,1337,1337,1337,1337};
	alpha_rk_interface_=alpha_rk;
	beta_rk_interface_=beta_rk;
	interpolation_choice_interface_="Second";
	gradient_choice_interface_="Least Squares";
	limiter_choice_interface_="Venkatakrishnan";
	flux_scheme_choice_interface_="Roe";
	residual_smoother_choice_interface_="Central IRS";
}

Interface::~Interface()
{
	
}