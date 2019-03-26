#ifndef SOLVERSKELETON_SRC_RESIDUALCALCULATOR_CPP
#define SOLVERSKELETON_SRC_RESIDUALCALCULATOR_CPP

#include "Block.h"

#include "FirstOrder.h"
#include "SecondOrder.h"
#include "Interpolation.h"

#include "RoeScheme.h"
#include "AusmScheme.h"
#include "FluxScheme.h"

#include "NoSmoother.h"
#include "CentralIrsSmoother.h"
#include "ResidualSmoother.h"

#include "ResidualCalculator.h"


#include <iostream>
using namespace std;

void ResidualCalculator::computeResidual(Block* block)
{
	//cout<<"\t\t\tExécution computeResidual: "<<endl;
	//cout<<endl<<"\t\t\tDans Interpolation"<<endl;
	interpolation_->computeInterpolation(block);
	//cout<<"\t\t\tFin Interpolation"<<endl;
	//cout<<endl<<"\t\t\tDans FluxScheme"<<endl;
	flux_scheme_->computeFluxConv(block);
	flux_scheme_->current_beta_=beta_rk_[current_stage_];
	if (beta_rk_[current_stage_]>(10^-16))
	{
		flux_scheme_->computeFluxDiss(block);
	}
	//cout<<"\t\t\tFin FluxScheme"<<endl;
	//cout<<endl<<"\t\t\tDans ResidualSmoother"<<endl;
	residual_smoother_->smoothResidual(block);
	//cout<<"\t\t\tFin ResidualSmoother"<<endl;
}


void ResidualCalculator::setInterpolation(int interpolation_choice, string gradient_choice, string limiter_choice, double omega, double k)
{
	delete interpolation_;
	if (interpolation_choice==2)
		interpolation_=new SecondOrder(gradient_choice, limiter_choice, omega, k);
	else
		interpolation_=new FirstOrder();
}

void ResidualCalculator::setFluxScheme(double gamma, string flux_scheme_choice)
{
	delete flux_scheme_;
	if (flux_scheme_choice=="roe")
		flux_scheme_=new RoeScheme(gamma);
	else if (flux_scheme_choice=="ausm")
		flux_scheme_=new AusmScheme();
}

void ResidualCalculator::setResidualSmoother(bool residual_smoother_choice)
{
	delete residual_smoother_;
	if (residual_smoother_choice==true)
		residual_smoother_=new CentralIrsSmoother();
	else
		residual_smoother_=new NoSmoother();
}


ResidualCalculator::ResidualCalculator(double gamma, std::vector<double> beta_rk, int interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, bool residual_smoother_choice, double omega, double k)

{
	current_stage_=0;
	beta_rk_=beta_rk;

	if (interpolation_choice==2)
		interpolation_=new SecondOrder(gradient_choice, limiter_choice, omega, k);
	else
		interpolation_=new FirstOrder();

	if (flux_scheme_choice=="roe")
		flux_scheme_=new RoeScheme(gamma);
	else if (flux_scheme_choice=="ausm")
		flux_scheme_=new AusmScheme();
	else
		flux_scheme_= NULL;

	if (residual_smoother_choice==true)
		residual_smoother_=new CentralIrsSmoother();
	else
		residual_smoother_=new NoSmoother();

}

ResidualCalculator::ResidualCalculator()

{
	interpolation_=NULL;
	flux_scheme_ = NULL;
	residual_smoother_=NULL;
}

ResidualCalculator::~ResidualCalculator()
{

}



#endif
