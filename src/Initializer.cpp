#ifndef SOLVERSKELETON_SRC_INITIALIZER_CPP
#define SOLVERSKELETON_SRC_INITIALIZER_CPP

#include "Interface.h"
#include "Solver.h"

#include "Initializer.h"

#include <string>
#include <iostream>
using namespace std;

Initializer::Initializer()

{
	
}


Initializer::~Initializer()
{

}

Solver* Initializer::initializeSolver(Interface* interface)
{
	cout<<"Initialisation du Solver"<<endl<<endl;

	double gamma=interface->gamma_interface_;
	double cfl=interface->cfl_interface_;
	int stage_number=interface->stage_number_interface_;
	double* alpha_rk=interface->alpha_rk_interface_;
	double* beta_rk=interface->beta_rk_interface_;
	string interpolation_choice=interface->interpolation_choice_interface_;
	string gradient_choice=interface->gradient_choice_interface_;
	string limiter_choice=interface->limiter_choice_interface_;
	string flux_scheme_choice=interface->flux_scheme_choice_interface_;
	string residual_smoother_choice=interface->residual_smoother_choice_interface_;

	return new Solver(gamma, cfl, stage_number, alpha_rk, beta_rk, interpolation_choice, gradient_choice, limiter_choice, flux_scheme_choice, residual_smoother_choice);

}


#endif