#ifndef SOLVERSKELETON_SRC_INTERFACE_CPP
#define SOLVERSKELETON_SRC_INTERFACE_CPP

#include "Interface.h"

#include <string>
#include <iostream>
using namespace std;

Interface::Interface(double gamma, double cfl, int stage_number, string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, string residual_smoother_choice)
{
	gamma_interface_=gamma;
	cfl_interface_=cfl;
	stage_number_interface_=stage_number;
	interpolation_choice_interface_=interpolation_choice;
	gradient_choice_interface_=gradient_choice;
	limiter_choice_interface_=limiter_choice;
	flux_scheme_choice_interface_=flux_scheme_choice;
	residual_smoother_choice_interface_=residual_smoother_choice;
}


Interface::Interface()
{
	gamma_interface_=1.5;
	cfl_interface_=1.0;
	stage_number_interface_=5;
	interpolation_choice_interface_="First";
	gradient_choice_interface_="Least Squares";
	limiter_choice_interface_="Venkatakrishnan";
	flux_scheme_choice_interface_="Roe";
	residual_smoother_choice_interface_="Central IRS";
}

Interface::~Interface()
{

}


#endif
