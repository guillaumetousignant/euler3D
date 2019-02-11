#ifndef SOLVERSKELETON_SRC_SOLVER_CPP
#define SOLVERSKELETON_SRC_SOLVER_CPP

#include "Block.h"
#include "Timestep.h"
#include "RungeKutta.h"
#include "Solver.h"

#include <string>
#include <iostream>
using namespace std;

Solver::Solver(double gamma, double cfl, int stage_number, double *alpha_rk, double *beta_rk,string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, string residual_smoother_choice)
{
	gamma_=gamma;
	timestep_= new Timestep(cfl);
	runge_kutta_= new RungeKutta(stage_number, alpha_rk, beta_rk, interpolation_choice, gradient_choice, limiter_choice, flux_scheme_choice,residual_smoother_choice);
}


Solver::~Solver()
{

}

Solver::Solver()
{
	timestep_=NULL;
	runge_kutta_=NULL;
}

void Solver::solve(Block* block)
{
	cout<<"Exécution solve: "<<block->test_block_<<endl;
	this->saveW0(block);
	cout<<endl<<"\tDans Timestep"<<endl;
	timestep_->computeSpectralRadius(block);
	timestep_->computeTimestep(block);
	cout<<"\tFin Timestep"<<endl;
	cout<<endl<<"\tDans RungeKutta"<<endl;
	runge_kutta_->computeRungeKutta(block);
	cout<<"\tFin RungeKutta"<<endl;
	cout<<"Fin de l'Exécution solve"<<endl;
}

void Solver::saveW0(Block* block)
{
	cout<<"\tExécution w0: "<<block->test_block_<<endl;
}


#endif