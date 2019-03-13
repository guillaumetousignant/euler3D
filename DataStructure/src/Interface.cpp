#include "Interface.h"

#include <string>
#include <iostream>

// Interface::Interface(string topology_file_name,string output_file_name, double gamma, double cfl, double angle_of_attack_rad, double angle_of_attack_deg, int stage_number, double mach, double cmac, string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, bool residual_smoothing, double omega, double k)
// {
// 	topology_file_name_interface_=topology_file_name;
// 	output_file_name_interface_=output_file_name;
// 	gamma_interface_=gamma;
// 	cfl_interface_=cfl;
// 	angle_of_attack_rad_interface_=angle_of_attack_rad;
// 	angle_of_attack_deg_interface_=angle_of_attack_deg;
// 	stage_number_interface_=stage_number;
// 	mach_interface_=mach;
// 	cmac_interface_=cmac;
// 	interpolation_choice_interface_=interpolation_choice;
// 	gradient_choice_interface_=gradient_choice;
// 	limiter_choice_interface_=limiter_choice;
// 	flux_scheme_choice_interface_=flux_scheme_choice;
// 	residual_smoothing_interface_=residual_smoothing;
// 	omega_interface_=omega;
// 	k_interface_=k;
// }

Interface::Interface(std::string output_file_name)
{
	output_file_name_interface_ = output_file_name;
}


Interface::Interface()
{	
	topology_file_name_interface_="default_topology.txt";
	output_file_name_interface_="default_output.txt";
	gamma_interface_=1.5;
	cfl_interface_=1.0;
	angle_of_attack_rad_interface_=0;
	angle_of_attack_deg_interface_=0;
	stage_number_interface_=5;
	mach_interface_=0.5;
	cmac_interface_=1;
	flux_scheme_order_choice_interface_="2";
	gradient_choice_interface_="Least Squares";
	limiter_choice_interface_="Venkatakrishnan";
	flux_scheme_choice_interface_="Roe";
	residual_smoothing_interface_=1;
	omega_interface_=1.0e-14;
	k_interface_=5;
}

Interface::~Interface()
{
	
}

void Interface::readInterfaceOutput()
{

	std::ifstream myfile(output_file_name_interface_);
	char topology_filename[200];
	char str_temp[200];
	std::string line;

	if (myfile.is_open())
	{

		getline(myfile, line);
		getline(myfile, line);
		sscanf (line.c_str(), "%s %s",str_temp,topology_filename);

		// To be complete!

	}
	myfile.close();

	// MESH
// topologyfilename
// topology.topo
// INPUT
// cfl gamma angleattackrad
// 7.5 1.4 0.00
// rkstage mach cmac
// 5 0.80 1.00
// nbitermax convcriterion
// 300 1e-15
// residual smoothing (0-no 1-yes)
// 1
// fluxscheme schemeorder
// roe 1
// gradient limiter
// greengauss barthjespersen
// omega k
// 1.0e6 5.00
// EXECUTABLE (0-no 1-yes)
// build execute
// 1 1
// OUTPUT (0-no 1-yes)
// clalpha cdalpha cmalpha
// 1 1 1
// clconv cdconv cmconv residualconv
// 1 1 1 1
// cpxc machcontour cpcontour
// 1 1 1
// slicecp
// 1
// axis xcoord ycoord zcoord
// x 1.00 1.00
}