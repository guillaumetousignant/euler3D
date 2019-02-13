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

	/*
	int nb_cells=block->n_cells_in_block_;
	int cell_idx;
	double ro, uu, vv, ww, pp;
	double ro_0,ru_0,rv_0,rw_0,re_0;

	for (cell_idx=0;cell_idx<nb_cells;cell_idx++) //BOUCLER SUR LES CELLULES INTÉRIEURS PLUTÔT? VA DÉPENDRE DE updateSolution
	{
		ro=block->primitive_variables_->ro_[cell_idx];
		uu=block->primitive_variables_->uu_[cell_idx];
		vv=block->primitive_variables_->vv_[cell_idx];
		ww=block->primitive_variables_->ww_[cell_idx];
		pp=block->primitive_variables_->pp_[cell_idx];

		ro_0=ro;
		ru_0= ro*uu;
		rv_0= ro*vv;
		rw_0= ro*ww;
		re_0= 0.5*ro*(uu*uu+vv*vv)+1./(gamma_-1.0)*pp;

		block->primitive_variables_->ro_0_[cell_idx]=ro_0;
		block->primitive_variables_->ru_0_[cell_idx]=ru_0;
		block->primitive_variables_->rv_0_[cell_idx]=rv_0;
		block->primitive_variables_->rw_0_[cell_idx]=rw_0;
		block->primitive_variables_->re_0_[cell_idx]=re_0;


	}

	*/
}


#endif