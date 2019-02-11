#ifndef SOLVERSKELETON_SRC_RUNGEKUTTA_CPP
#define SOLVERSKELETON_SRC_RUNGEKUTTA_CPP

#include "Block.h"
#include "ResidualCalculator.h"
#include "Updater.h"
#include "RungeKutta.h"

#include <string>
#include <iostream>
using namespace std;

RungeKutta::RungeKutta(int stage_number, double *alpha_rk, double *beta_rk,string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice,string residual_smoother_choice)

{
	stage_number_=stage_number;
	updater_=new Updater();
	residual_calculator_=new ResidualCalculator(interpolation_choice, gradient_choice, limiter_choice, flux_scheme_choice, residual_smoother_choice);
	alpha_rk_=alpha_rk;
	beta_rk_=beta_rk;
}


RungeKutta::~RungeKutta()
{

}

void RungeKutta::computeRungeKutta(Block* block)
{
	cout<<"\t\tExécution computeRungeKutta: "<<block->test_block_<<endl;
	cout<<endl<<"\t\tDans ResidualCalculator"<<endl;
	residual_calculator_->computeResidual(block);
	cout<<"\t\tFin ResidualCalculator"<<endl;
	cout<<endl<<"\t\tDans Updater"<<endl;
	updater_->updateInternalBlock(block);
	updater_->updateBoundary(block);
	cout<<"\t\tFin Updater"<<endl;
}


#endif