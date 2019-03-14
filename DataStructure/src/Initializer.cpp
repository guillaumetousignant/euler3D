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
	int interpolation_choice=interface->interpolation_choice_interface_;
	string gradient_choice=interface->gradient_choice_interface_;
	string limiter_choice=interface->limiter_choice_interface_;
	string flux_scheme_choice=interface->flux_scheme_choice_interface_;
	bool residual_smoother_choice=interface->residual_smoother_choice_interface_;

	int n_blocks=interface->n_blocks_interface_;
	int max_iter=interface->max_iter_interface_;
	double convergence_criterion=interface->convergence_criterion_interface_;
	double cmac=interface->cmac_interface_;
	double aoa_deg= interface->aoa_deg_interface_;
	double mach_aircraft=interface->mach_aircraft_interface_;

	double omega=interface->omega_interface_;
	double k=interface->k_interface_;

	return new Solver(gamma, cfl, stage_number, interpolation_choice, gradient_choice, limiter_choice, flux_scheme_choice, residual_smoother_choice, n_blocks, max_iter, convergence_criterion, cmac, aoa_deg, mach_aircraft, omega, k);

}

CompleteMesh* Initializer::InitializeMesh(Interface* interface)
{

	// cout<<"Initialisation du maillage entier"<<endl<<endl;
	// string mesh_file_name=interface->mesh_file_name_interface_;
	/*
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
	int n_blocks_=n_blocks;
	int n_blocks_in_process_=n_blocks_in_process;
	int* my_blocks_=my_blocks;
	Block* all_blocks_=all_blocks;

	return new CompleteMesh(int n_blocks, int n_blocks_in_process, int* my_blocks[], Block* all_blocks_[]);
*/
}


#endif
