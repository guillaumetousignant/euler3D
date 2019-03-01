#include "Interface.h"

#include <string>
#include <iostream>
using namespace std;

Interface::Interface(string topology_file_name,string output_file_name, double gamma, double cfl, double angle_of_attack_rad, double angle_of_attack_deg, int stage_number, double mach, double cmac, string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, bool residual_smoothing, double omega, double k)
{
	topology_file_name_interface_=topology_file_name;
	output_file_name_interface_=output_file_name;
	gamma_interface_=gamma;
	cfl_interface_=cfl;
	angle_of_attack_rad_interface_=angle_of_attack_rad;
	angle_of_attack_deg_interface_=angle_of_attack_deg;
	stage_number_interface_=stage_number;
	mach_interface_=mach;
	cmac_interface_=cmac;
	interpolation_choice_interface_=interpolation_choice;
	gradient_choice_interface_=gradient_choice;
	limiter_choice_interface_=limiter_choice;
	flux_scheme_choice_interface_=flux_scheme_choice;
	residual_smoothing_interface_=residual_smoothing;
	omega_interface_=omega;
	k_interface_=k;
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
	interpolation_choice_interface_="Second";
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