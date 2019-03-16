#ifndef SOLVERSKELETON_SRC_RUNGEKUTTA_CPP
#define SOLVERSKELETON_SRC_RUNGEKUTTA_CPP

#include "Block.h"
#include "ResidualCalculator.h"
#include "Updater.h"
#include "RungeKutta.h"

#include <string>
#include <iostream>
using namespace std;

RungeKutta::RungeKutta(double gamma, int stage_number, int interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, bool residual_smoother_choice, double omega, double k)

{
	stage_number_=stage_number;


	double alpha_rk[5];
	double beta_rk[5];

	switch(stage_number_)
	{
		case 1:
		alpha_rk[0]=1.0;
		beta_rk[0]=1.0;
		break;
		case 2:
		alpha_rk[0]=0.6;
		alpha_rk[1]=1.0;
		beta_rk[0]=1.0;
		beta_rk[1]=0.0;
		break;
		case 3:
		alpha_rk[0]=0.6;
		alpha_rk[1]=0.6;
		alpha_rk[2]=1.0;
		beta_rk[0]=1.0;
		beta_rk[1]=0.0;
		beta_rk[2]=0.0;
		break;
		case 4:
		alpha_rk[0]=0.25;
		alpha_rk[1]=1.0/3.0;
		alpha_rk[2]=0.5;
		alpha_rk[3]=1.0;
		beta_rk[0]=1.0;
		beta_rk[1]=0.5;
		beta_rk[2]=0.0;
		beta_rk[3]=0.0;
		break;
		case 5:

		alpha_rk[0]=0.2742;
		alpha_rk[1]=0.2067;
		alpha_rk[2]=0.5020;
		alpha_rk[3]=0.5142;
		alpha_rk[4]=1.0;
		beta_rk[0]=1.0;
		beta_rk[1]=0.0;
		beta_rk[2]=0.56;
		beta_rk[3]=0.0;
		beta_rk[4]=0.44;

		break;
		default:
		cerr << "Invalid number of RK stages" << endl;
	}

	updater_=new Updater(gamma, alpha_rk);
	residual_calculator_=new ResidualCalculator(gamma, beta_rk, interpolation_choice, gradient_choice, limiter_choice, flux_scheme_choice, residual_smoother_choice, omega, k);
}


RungeKutta::~RungeKutta()
{

}

void RungeKutta::computeRungeKutta(Block* block)
{
	cout<<"\t\tExécution computeRungeKutta: "<<endl;
	cout<<endl<<"\t\tDans ResidualCalculator"<<endl;
	residual_calculator_->computeResidual(block);
	cout<<"\t\tFin ResidualCalculator"<<endl;
	cout<<endl<<"\t\tDans Updater"<<endl;
	updater_->updateInternalBlock(block);
	updater_->updateBoundary(block);
	cout<<"\t\tFin Updater"<<endl;



	int stage_idx;

	for (stage_idx=0;stage_idx<stage_number_;stage_idx++)
	{
		residual_calculator_->current_stage_=stage_idx;
		residual_calculator_->computeResidual(block);
		updater_->current_stage_=stage_idx;
		updater_->updateInternalBlock(block);
		updater_->updateBoundary(block);
	}




}


#endif
