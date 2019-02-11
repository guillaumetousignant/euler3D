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
	cout<<"\t\t\tExécution computeResidual: "<<block->test_block_<<endl;
	cout<<endl<<"\t\t\tDans Interpolation"<<endl;
	interpolation_->computeInterpolation(block);
	cout<<"\t\t\tFin Interpolation"<<endl;
	cout<<endl<<"\t\t\tDans FluxScheme"<<endl;
	flux_scheme_->computeFlux(block);
	cout<<"\t\t\tFin FluxScheme"<<endl;
	cout<<endl<<"\t\t\tDans ResidualSmoother"<<endl;
	residual_smoother_->smoothResidual(block);
	cout<<"\t\t\tFin ResidualSmoother"<<endl;
}


void ResidualCalculator::setInterpolation(string interpolation_choice, string gradient_choice, string limiter_choice)
{
	delete interpolation_;
	if (interpolation_choice=="Second")
		interpolation_=new SecondOrder(gradient_choice, limiter_choice);
	else
		interpolation_=new FirstOrder();
}

void ResidualCalculator::setFluxScheme(string flux_scheme_choice)
{
	delete flux_scheme_;
	if (flux_scheme_choice=="Roe")
		flux_scheme_=new RoeScheme();
	else if (flux_scheme_choice=="AUSM")
		flux_scheme_=new AusmScheme();
}

void ResidualCalculator::setResidualSmoother(string residual_smoother_choice)
{
	delete residual_smoother_;
	if (residual_smoother_choice=="Central IRS")
		residual_smoother_=new CentralIrsSmoother();
	else
		residual_smoother_=new NoSmoother();
}


ResidualCalculator::ResidualCalculator(string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, string residual_smoother_choice)

{
	if (interpolation_choice=="Second")
		interpolation_=new SecondOrder(gradient_choice, limiter_choice);
	else
		interpolation_=new FirstOrder();

	if (flux_scheme_choice=="Roe")
		flux_scheme_=new RoeScheme();
	else if (flux_scheme_choice=="AUSM")
		flux_scheme_=new AusmScheme();
	else
		flux_scheme_= NULL;

	if (residual_smoother_choice=="Central IRS")
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
